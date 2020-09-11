/*
 * KerSem.cpp
 *
 *  Created on: Sep 5, 2020
 *      Author: OS1
 */

#include "KerSem.h"
#include "ListSem.h"

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
}
void KerSem::unblock(){
	PCB* pom = this->listaBlokiranihNaSemaforu->get();
	pom->state = PCB::READY;

}

int KerSem::wait(Time maxTimeToWait){
	Global::lock();

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

	if(maxTimeToWait!=0) return 1;
	return 0;

	Global::unlock();
}
int KerSem::signal(int n){
	Global::lock();
	if(n<0) return n; // ako je negativni broj

	if(n == 0) n=1;

	if(this->listaBlokiranihNaSemaforu->num < n) n = listaBlokiranihNaSemaforu->num;

	semVal+=n;
	for(int i=0;i<n;i++)
		unblock();

	return n;
	Global::unlock();
}

KerSem::~KerSem() {
	// TODO Auto-generated destructor stub
	Global::lock();
	((ListSem*)Global::listOfSemaphores)->remove(this);
	Global::unlock();
}

