/*
 * ListPCB.cpp
 *
 *  Created on: Sep 4, 2020
 *      Author: OS1
 */

#include "ListPCB.h"
#include "PCB.h"
#include "SCHEDULE.H"
ListPCB::ListPCB() {
	// TODO Auto-generated constructor stub
	first=last=0;

}

void ListPCB::listDel(){
	Elem* pom = 0;
	while(first){
		pom=first;
		first=first->next;
		pom->pcb = 0;
		pom->next=0;
		delete pom;
	}
	first=last=0;
}

void ListPCB::add(PCB* pcb1){
	Elem *novi = new Elem(pcb1);
	if(!first)
		first=last=novi;
	else
		last=last->next=novi;
}

PCB* ListPCB::get() {
	Elem* pom;
	PCB* pcbret;
	if(!first)return 0;
	pom=first;
	pcbret=pom->pcb;
	first=first->next;
	if(first==0)
		first=last=0;
	delete pom;
	return pcbret;
}
ListPCB::~ListPCB() {
	listDel();
}

void ListPCB::oslobodiBlokirane(){
	if(!first) return;
	for(Elem* tek =first; tek; tek=tek->next){
		Global::lock();
		tek->pcb->state = PCB::READY;
		Scheduler::put(tek->pcb);
		Global::unlock();
	}
	delete this;
}
