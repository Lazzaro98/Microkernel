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

void Queue::ispisiListu(){
	Elem* pom = first;
	syncPrintf("Red cekanja izlgeda ovako: ");
	while(pom){
		syncPrintf("%d ", pom->pcb->getId());
		pom=pom->next;
	}
	syncPrintf("\n");
}



Queue::~Queue() {
	// TODO Auto-generated destructor stub
	Elem* pom = 0;
		while(first) {
			pom = first;
			first = first->next;
			pom->pcb = 0;
			pom->next=0;
			delete pom;
		}
	first=last=0;
}


void Queue::timeDec(){
	Global::lock();
	Elem* k = first,*pom = 0;
	while(k!=0)
		if(k->timeToWait-->0){
			if(!k->timeToWait){
				k->pcb->blkFlag=0;
				k->pcb->state = PCB::READY;
				Scheduler::put(k->pcb);
				num--;
				if(k == first){
					if(first == last) first=last=0;
					else first=first->next;
					delete k;
					k=first;
				}else {
					pom->next=k->next;
					k->next=0;
					if(k==last) last=pom;
					delete k;
					k=pom->next;
				}
			} else{
				pom=k;
				k=k->next;
			}
		}
	Global::unlock();
}

void Queue::put(PCB* pcb1,Time time1){
	Elem* novi = new Elem(pcb1,time1);
	if(!first) first = last = novi;
	else last = last->next = novi;
	//syncPrintf(" + Pre nego sto putujem broj onih koji cekaju je %d. ", num);
	pcb1->blkFlag=1;
	num++;
	//syncPrintf("Putovano i sada ih ima %d\n",num);
}

PCB* Queue::get(){
	if(!first)return 0;
	Elem* del = first;
	first->pcb->blkFlag=1;
	PCB* pom = first->pcb;
	first = first->next;
	//syncPrintf(" - Pre nego sto getujem broj onih koji cekaju je %d. ", num);
	num--;
	//syncPrintf("Getovano i sada ih ima %d\n",num);
	del->pcb = 0;
	del->next = 0;
	delete del;
	return pom;
}


