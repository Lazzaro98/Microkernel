/*
 * ListPCB.cpp
 *
 *  Created on: Sep 4, 2020
 *      Author: OS1
 */

#include "ListPCB.h"
#include "PCB.h"
#include "SCHEDULE.H"

extern int syncPrintf(const char *format, ...);

ListPCB::ListPCB() {
	// TODO Auto-generated constructor stub
	first=last=0;
}


PCB* ListPCB::get() {
	if(!first) return 0;
	Elem* pom=first;
	PCB* ret = pom->pcb;
	delete pom;
	if(first->next==0)first=last=0;
	else first=first->next;
	return ret;
}

void ListPCB::oslobodiBlokirane(){
	if(!first) return;
	for(Elem* tek =first; tek; tek=tek->next){
		Global::lock();
		tek->pcb->state = PCB::READY;
		Scheduler::put(tek->pcb);
		Global::unlock();
		//syncPrintf("oslobadjam Blokirane---------------\n");
	}
}

ListPCB::~ListPCB() {
	Elem* pom = 0;
		while(first){
			pom=first;
			first=first->next;
			pom->pcb = 0;
			pom->next=0;
			delete pom;
		}
		first = last = 0;
}

void ListPCB::add(PCB* pcb1){
	Elem *novi = new Elem(pcb1);
	if(!first) first=last=novi;
	else last=last->next=novi;
}

void ListPCB::ispisiListu(){
	Elem* pom = first;
	while(pom){
		syncPrintf("%d ",pom->pcb->id);
		pom=pom->next;
	}
}

