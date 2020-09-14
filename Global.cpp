/*
 * Global.cpp
 *
 *  Created on: Aug 29, 2020
 *      Author: OS1
 */

#include "Global.h"
#include "ListThr.h"
#include "ListSem.h"
#include<dos.h>
#include "idle.h"
Global::Global() {
	// TODO Auto-generated constructor stub

}
volatile int Global::zahtevana_promena_konteksta = 0;
volatile PCB* Global::running = 0;
volatile int Global::lockFlag = 0;
volatile ListThr* Global::listOfThreads = new ListThr();
volatile PCB* Global::idleTr = 0;
volatile ListSem* Global::listOfSemaphores = new ListSem();

Global::~Global() {
	// TODO Auto-generated destructor stub
}

void Global::dodaj(Thread* thread){
	//listOfThr
#ifndef BCC_BLOCK_IGNORE
	Global::listOfThreads->add(thread);
#endif
}

void Global::lock(){
	lockFlag=1;
}

void Global::unlock(){
	lockFlag = 0;
	if(zahtevana_promena_konteksta)
		PCB::dispatch(); //valjda je dobro ovo hm
}

void Global::timeDec(){
#ifndef BCC_BLOCK_IGNORE
	Global::listOfSemaphores->timeDecrementAll();
#endif
}

typedef void interrupt (*pInterrupt)(...);

static pInterrupt oldInterrupt;
volatile PCB* Global::mainThread = 0;

void Global::inicInterrupt(){
	Global::lock();
#ifndef BCC_BLOCK_IGNORE
	oldInterrupt = getvect(0x8);
	setvect(0x8,(pInterrupt)PCB::timer);
	setvect(0x60,oldInterrupt);
#endif
	Global::idleTr = (new idle())->myPCB;
	Global::idleTr->myThread->start();
	Global::mainThread = (new Thread(0,2))->myPCB;
	mainThread->state = PCB::READY;
	running=mainThread;
	PCB::brojac = running->timeSlice;
	Global::unlock();
}

void Global::restoreInterrupt(){
	Global::lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(0x8,oldInterrupt);
#endif
	Global::unlock();
}
