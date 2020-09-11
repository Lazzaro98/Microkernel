/*
 * Global.cpp
 *
 *  Created on: Aug 29, 2020
 *      Author: OS1
 */

#include "Global.h"
#include "ListThr.h"
#include "ListSem.h"

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
