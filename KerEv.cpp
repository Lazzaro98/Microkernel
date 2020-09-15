/*
 * KerEv.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */

#include "KerEv.h"
#include "IVTEntry.h"
#include "SCHEDULE.h"

typedef unsigned char IVTNo;

KerEv::KerEv(IVTNo ivtNo) {
	// TODO Auto-generated constructor stub
	entrynum=ivtNo;
	evVal=0;
	myThread=(PCB*)Global::running;
	blocked=0;
	//IVTEntry::table[ivtNo]->myImpl=this;
#ifndef BCC_BLOCK_IGNORE
	IVTEntry::dodaj(ivtNo, this);
#endif
}

KerEv::~KerEv() {
	// TODO Auto-generated destructor stub
	if(blocked){
		blocked->state=PCB::READY;
		Scheduler::put(blocked);
	}
	delete blocked;
	delete myThread;
	blocked=0;
	myThread=0;
}

void KerEv::wait(){
	if((PCB*)Global::running != myThread)return;
	Global::lock();
	if(evVal==0){
		myThread->state = PCB::BLOCKED;
		blocked=myThread;
		PCB::dispatch();
	}
	else{
		evVal=0;
	}
	Global::unlock();
}


void KerEv::signal(){
	Global::lock();
	if(!blocked)
		evVal=1;
	else {
		myThread->state = PCB::READY;
		blocked=0;
		Scheduler::put(myThread);
		PCB::dispatch();
	}
	Global::unlock();
}
