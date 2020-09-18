/*
 * KerSem.cpp
 *
 *  Created on: Sep 5, 2020
 *      Author: OS1
 */

#include "KerSem.h"
#include "ListSem.h"
#include "SCHEDULE.H"

extern int syncPrintf(const char *format, ...);

KerSem::KerSem(int initVal, Semaphore* sem1) {
	// TODO Auto-generated constructor stub
	sem = sem1;
	semVal = initVal;
	testId=0;
	((ListSem*)Global::listOfSemaphores)->add(this);
	listaBlokiranihNaSemaforu = new Queue();
}

void KerSem::setTestId(int id1){
	this->testId=id1;
}

KerSem::~KerSem() {
	// TODO Auto-generated destructor stub
	Global::lock();
	((ListSem*)Global::listOfSemaphores)->remove(this);
	Global::unlock();
}

void KerSem::block(Time timeToWait1){
	if(Global::running == Global::idleTr) return;
	Global::running->state = PCB::BLOCKED;
	int time;
	if(timeToWait1 == 0)
		{
		time = -1;
		}
	else {
		time=timeToWait1;
	}
	//syncPrintf("Sada cu dodati na liostu semafora\n");
	listaBlokiranihNaSemaforu->put((PCB*)Global::running, time);
	//syncPrintf("Dodao sam na listu i sada ih ima %d\n",listaBlokiranihNaSemaforu->num);
}

int KerSem::wait(Time maxTimeToWait){
	int time;
	if(maxTimeToWait>=0)
	{
		time = maxTimeToWait;
	}
	else
	{
		time = 0;
	}

	semVal--;
	if(semVal<0){
		block(maxTimeToWait);
		PCB::dispatch();
	}
	else {
		Global::running->blkFlag=1;
	}
	if(!Global::running->blkFlag) semVal++;
	if(Global::running->blkFlag) return 1;
	else return 0;
}
int KerSem::signal(int n){

	if(n<0){}
	else if(n==0){
		semVal++;
		if(semVal<0)
		{
			PCB* pom = this->listaBlokiranihNaSemaforu->get();
			//syncPrintf("Skinuo sam sa liste i sada ih ima %d\n",listaBlokiranihNaSemaforu->num);
			pom->state = PCB::READY;
			Scheduler::put(pom);
		}
	}
	else {
		int pom=n;
		if(n>listaBlokiranihNaSemaforu->num) n=listaBlokiranihNaSemaforu->num;
		for(int i=0;i<n;i++) {
			PCB* pom = this->listaBlokiranihNaSemaforu->get();
			//syncPrintf("Skinuo sam sa liste i sada ih ima %d\n",listaBlokiranihNaSemaforu->num);
			pom->state = PCB::READY;
			Scheduler::put(pom);
		}
		semVal=semVal+pom;
	}
	return n;
}

