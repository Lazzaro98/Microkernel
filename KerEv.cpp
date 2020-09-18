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
	IVTEntry::table[ivtNo]->myImpl=this;
}

void KerEv::unisti(){
	if(blocked) staviUskedz(blocked);
	delete blocked;
	blocked=0;
	myThread=0;
}

void KerEv::signal(){
	Global::lock();
	if(blocked) {
		staviUskedz(myThread);
		blocked=0;
		Global::running->dispatch();
	}
	else evVal=0;
	Global::unlock();
}

KerEv::~KerEv() {
	// TODO Auto-generated destructor stub
	this->unisti();
}


void KerEv::wait(){
	if((PCB*)Global::running != myThread)return;
	Global::lock();
	if(!evVal){
		myThread->state = PCB::BLOCKED;
		blocked=myThread;
		PCB::dispatch();
	}
	else evVal=0;
	Global::unlock();
}


void KerEv::staviUskedz(PCB* nit){
	nit->state=PCB::READY;
	Scheduler::put(nit);
}
