/*
 * Queue.cpp
 *
 *  Created on: Sep 3, 2020
 *      Author: OS1
 */

#include "Queue.h"
#include "PCB.h"
#include "SCHEDULE.H"

extern int syncPrintf(const char *format, ...);

Queue::Queue() {
	// TODO Auto-generated constructor stub
	first = last = 0;
	num=0;
}

Queue::~Queue() {
	// TODO Auto-generated destructor stub
	emptyList();
}

void Queue::put(PCB* pcb1,Time time1){
	pcb1->blkFlag=1;
	Elem* novi = new Elem(pcb1,time1);
	if(first == 0)
		first = last = novi;
	else
		last = last->next = novi;
	//syncPrintf(" + Pre nego sto putujem broj onih koji cekaju je %d. ", num);
	num++;
	//syncPrintf("Putovano i sada ih ima %d\n",num);
}

PCB* Queue::get(){
	if(first == 0)
		return 0;
	PCB* pom = first->pcb;
	pom->blkFlag = 1;
	Elem* del = first;
	first = first->next;
	del->pcb = 0;
	del->next = 0;
	delete del;
	//syncPrintf(" - Pre nego sto getujem broj onih koji cekaju je %d. ", num);
	num--;
	//syncPrintf("Getovano i sada ih ima %d\n",num);
	return pom;
}

void Queue::emptyList(){
	Elem* pom = 0;
	while(first) {
		pom = first;
		first = first->next;
		pom->pcb = 0;
		delete pom;
	}
	first=last=0;
}

void Queue::timeDec(){
	Global::lock();
	Elem* k = first,*pom = 0;
	while(k){
		if(k->timeToWait>0) k->timeToWait--;
		if(k->timeToWait==0){ // treba ga izbaciti iz liste. Pamticemo trenutni i prethodni da bismo mogli lako de prevezemo listu
			if(k == first){
				k->pcb->blkFlag = 0;
				k->pcb->state = PCB::READY;
				Scheduler::put(k->pcb);
				delete k;
				first = last = 0;
				k = pom = 0;
			}
			else {
				k->pcb->blkFlag = 0;
				k->pcb->state = PCB::READY;
				Scheduler::put(k->pcb);
				pom->next = k->next;
				delete k;
				k = pom->next;
				pom = k;
				k=k->next;
			}
			num--;
		}
		else {
		pom = k;
		k=k->next;
	}
	Global::unlock();
}
}
