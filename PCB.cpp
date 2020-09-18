/*
 * PCB.cpp
 *
 *  Created on: Aug 29, 2020
 *      Author: OS1
 */

#include "PCB.h"
#include "SCHEDULE.H"
#include <dos.h>
#include "Global.h"
//#include "ListThr.h"
#include "ListPCB.h"
#define MAX_STACK_SIZE 65535

volatile static unsigned tss;
volatile static unsigned tbp;
volatile static unsigned tsp;

class Global;

extern void tick();

extern int syncPrintf(const char *format, ...);

volatile unsigned PCB::brojac=20; //ovde nesto nije htelo hm
//ListThr *PCB::listOfThreads = new ListThr();
static ID id_br = 0;

PCB::PCB(Time timeSlice1, Thread* myThread1, StackSize stackSize1) {
	// TODO Auto-generated constructor stub
	StackSize stacksizex;
	if(stackSize1>MAX_STACK_SIZE) stacksizex = MAX_STACK_SIZE;
	else stacksizex=stackSize1;
	timeSlice = timeSlice1;
	state = CREATED;
	myThread = myThread1;
	stackSize = stacksizex;
	id = id_br++;
	blkFlag = 1;
	ss=0;sp=0;bp=0;
	stack  = new unsigned[stackSize];
	//Global::dodaj(myThread);
	listBlokiranih = new ListPCB();
}

void PCB::dispatch(){
	// <------------- Greska u sledecih 4 linije, najverovatnije u tajmeru
	//if(Global::waitToCompleteTest==10)return;
	asm cli
	Global::zahtevana_promena_konteksta = 1;
	timer();
	asm sti
//	syncPrintf("zavrsio sam dispatch.--------------------------\n");
}
void PCB::wrapper(){
	Global::running->myThread->run();
	//ncPrintf("Sada cu da poyovem oslobodiBlokirane\n");
	Global::running->listBlokiranih->oslobodiBlokirane(); //kada nit zavrsi s izvrsavanjem, oslobodi sve one koje su cekale nju da se zavrsi
	//ncPrintf("Pozvao sam oslobodiBlokirane\n");
	Global::running->state=FINISHED;
	//PCB::dispatch();
	//izadji ovde

}
void PCB::createProcess() {
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize - 3] = FP_SEG(dispatch);
	stack[stackSize - 4] = FP_OFF(dispatch);
	stack[stackSize - 5] = 0x200;
	stack[stackSize - 6] = FP_SEG(wrapper);
	stack[stackSize - 7] = FP_OFF(wrapper);

	ss = FP_SEG(stack+stackSize-16);
	sp = FP_OFF(stack+stackSize-16);
	bp=sp;
#endif
	this->state = READY;

	if(this != Global::idleTr) Scheduler::put(this);

}

PCB::~PCB() {
	// TODO Auto-generated destructor stub
	this->myThread = 0;
	delete[] stack;
	stack = 0;
	delete listBlokiranih;
}

ID PCB::getId(){
	return id;
}

void interrupt PCB::timer(){
	if(Global::zahtevana_promena_konteksta==0){
		tick();
		Global::timeDec();
		if(PCB::brojac>0)
			if(((PCB*)Global::running)->timeSlice!=0)
				PCB::brojac--;
	}
	if((PCB::brojac == 0 && Global::running->timeSlice!=0) || Global::zahtevana_promena_konteksta){
		/*if(Global::zahtevana_promena_konteksta){
			syncPrintf("---------------------test\n");
		}*/
				asm {
					mov tss, ss
					mov tsp, sp
					mov tbp, bp
				}
				Global::running->ss = tss;
				Global::running->sp = tsp;
				Global::running->bp = tbp;

				if(Global::running->state==PCB::READY && (PCB*)Global::running!=(PCB*)Global::idleTr)
					Scheduler::put((PCB*)Global::running);

				Global::running = Scheduler::get();

				if(Global::running==0) Global::running = Global::idleTr;

				tsp = Global::running->sp;
				tss = Global::running->ss;
				tbp = Global::running->bp;

				PCB::brojac = ((PCB*)Global::running)->timeSlice;

				asm{
					mov ss,tss
					mov sp, tsp
					mov bp, tbp
				}
	}
				if(!Global::zahtevana_promena_konteksta) asm int 60h;
				Global::zahtevana_promena_konteksta = 0;


}

//scheduler ne radi iz nekog razloga. Probaj sutra da prekucas ceo kod i da svuda stavljas PCB umesto PCB. Moguce da je to zeznulo stvar.
