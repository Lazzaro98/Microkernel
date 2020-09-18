/*
 * Global.cpp
 *
 *  Created on: Aug 29, 2020
 *      Author: OS1
 */

#include "Global.h"
//#include "ListThr.h"
#include "ListSem.h"
#include<dos.h>
#include "idle.h"
Global::Global() {
	// TODO Auto-generated constructor stub
	waitToCompleteTest = 0;
}
volatile int Global::waitToCompleteTest= 0;
volatile int Global::zahtevana_promena_konteksta = 0;

volatile int Global::lockFlag = 0;

volatile ListSem* Global::listOfSemaphores = new ListSem();

Global::~Global() {
	// TODO Auto-generated destructor stub
	mainThread = idleTr = 0;
}

void Global::dodaj(Thread* thread){
	//listOfThr
#ifndef BCC_BLOCK_IGNORE
	//Global::listOfThreads->add(thread);
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

static pInterrupt oldInt;


void Global::restoreInterrupt(){
	Global::lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(0x8,oldInt);
#endif
	Global::unlock();
}

volatile PCB* Global::mainThread = 0;
volatile PCB* Global::idleTr = 0;
volatile PCB* Global::running = 0;


void Global::inicInterrupt(){
	Global::lock();
#ifndef BCC_BLOCK_IGNORE
	oldInt = getvect(0x8);
	setvect(0x8,(pInterrupt)PCB::timer);
	setvect(0x60,oldInt);
#endif
		Thread *main = new Thread(0,2);
		Global::mainThread = main->myPCB;
		mainThread->state = PCB::READY;
		idle *tidle = new idle(300,2);
		Global::idleTr = tidle->myPCB;
		Global::idleTr->myThread->start();
		running=mainThread;
		PCB::brojac = running->timeSlice;
		Global::unlock();
}


