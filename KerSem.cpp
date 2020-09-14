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

KerSem::KerSem(int init, Sem* sem1) {
	// TODO Auto-generated constructor stub
	Global::lock();
	sem = sem1;
	semVal = init;
	listaBlokiranihNaSemaforu = new Queue();
	((ListSem*)Global::listOfSemaphores)->add(this);
	Global::unlock();
}
void KerSem::block(Time timeToWait1){
	if(Global::running == Global::idleTr) return;
	if(timeToWait1 == 0) timeToWait1 = -1;
	Global::running->state = PCB::BLOCKED;
	listaBlokiranihNaSemaforu->put((PCB*)Global::running, timeToWait1);
	//syncPrintf("Dodao sam na listu i sada ih ima %d\n",listaBlokiranihNaSemaforu->num);
}
void KerSem::unblock(){
	PCB* pom = this->listaBlokiranihNaSemaforu->get();
	//syncPrintf("Skinuo sam sa liste i sada ih ima %d\n",listaBlokiranihNaSemaforu->num);
	pom->state = PCB::READY;
	Scheduler::put(pom);
}

int KerSem::wait(Time maxTimeToWait){
	Global::lock();
	if(maxTimeToWait<0) maxTimeToWait=0;
	semVal--;
	if(semVal<0){
		block(maxTimeToWait);
		Global::unlock();
		Global::running->dispatch();
	}
	else {
		Global::running->blkFlag = 1;
		Global::unlock();
	}

	/*if(maxTimeToWait!=0) return 1;
	Global::unlock();
	return 0;*/
	if(Global::running->blkFlag==0)
		semVal++;
	return Global::running->blkFlag;
}
int KerSem::signal(int n){
	Global::lock();
	if(n<0) return n; // ako je negativni broj

	if(n == 0) n=1;
	//syncPrintf("broj blokiranih je %d\n",n);
	//if(this->listaBlokiranihNaSemaforu->num < n) n = listaBlokiranihNaSemaforu->num;
	//syncPrintf("broj blokiranih je %d\n",n);
	semVal+=n;
	for(int i=0;i<n;i++)
		unblock();
	Global::unlock();
	return n;

}

KerSem::~KerSem() {
	// TODO Auto-generated destructor stub
	Global::lock();
	((ListSem*)Global::listOfSemaphores)->remove(this);
	Global::unlock();
}

