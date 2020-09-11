/*
 * Thread.cpp
 *
 *  Created on: Aug 29, 2020
 *      Author: OS1
 */

#include "Thread.h"
#include "PCB.h"
#include "Global.h"
#include "ListThr.h"

class PCB;
class Global;

Thread::Thread(StackSize stackSize, Time timeSlice) {
	// TODO Auto-generated constructor stub
	myPCB = new PCB(timeSlice,this,stackSize);
}

Thread::~Thread() {
	// TODO Auto-generated destructor stub
	delete myPCB;
	myPCB=0;
	waitToComplete();
}

void Thread::start(){
	if(this->myPCB != 0 && this->myPCB->state == PCB::CREATED){
		Global::lock();
		this->myPCB->createProcess();
		Global::unlock();
	}
}

int Thread::getId(){
	return this->myPCB->id;
}

Thread* Thread::getThreadById(ID id1){
	return Global::listOfThreads->getThreadById(id1);
}

ID Thread::getRunningId() {
	return Global::running->id;
}

void Thread::dispatch(){
	Global::running->dispatch();
}
extern int syncPrintf(const char *format, ...);
void Thread::waitToComplete(){
	Global::lock();
	if(myPCB == 0 || myPCB->state == PCB::FINISHED || myPCB == (PCB*)Global::running){ // dodaj main
		Global::unlock();
		//syncPrintf("%d Nisam uradio nista\n", myPCB->myThread->getId());
		return;
	}
	//syncPrintf("%d se blokirala i prepustila vreme drugom procesu\n",myPCB->myThread->getId());
	Global::running->state = PCB::BLOCKED;
	//u pcb od t1 stavi pcb running
	//red blokiranih u pcbu
	//u wrapperu prodjem kroz red od niti i vratim ih u scheduler i promenim im stanje
	this->myPCB->listBlokiranih->add((PCB*)Global::running);
	PCB::dispatch();
	Global::unlock();
}
