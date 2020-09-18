/*
 * Thread.cpp
 *
 *  Created on: Aug 29, 2020
 *      Author: OS1
 */

#include "Thread.h"
#include "PCB.h"
#include "Global.h"
//#include "ListThr.h"

class PCB;
class Global;

Thread::Thread(StackSize stackSize, Time timeSlice) {
	// TODO Auto-generated constructor stub
	myPCB = new PCB(timeSlice,this,stackSize);
}

Thread::~Thread() {
	// TODO Auto-generated destructor stub
	waitToComplete();
	delete myPCB;
	myPCB = 0;

}

void Thread::start(){
	if(this->myPCB != 0 && this->myPCB->state == PCB::CREATED){
		Global::lock();
		if(myPCB!=0) this->myPCB->createProcess();
		Global::unlock();
	}
}

ID Thread::getId(){
	return this->myPCB->id;
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
	if(myPCB != (PCB*)Global::running && myPCB!=0 && myPCB->state != PCB::FINISHED){
		Global::running->state = PCB::BLOCKED;
		myPCB->listBlokiranih->add((PCB*)Global::running);
		Global::unlock();
		//syncPrintf("Pokrecem dispatch u waitToComplete-u. ID = %d \n",Global::running->id);
		PCB::dispatch();
		//syncPrintf("Izasao sam iz waitToCompelte-a. ID = %d \n ", Global::running->id);
	}
	else {
		Global::unlock();
	}
}


