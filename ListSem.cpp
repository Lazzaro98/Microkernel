/*
 * ListSem.cpp
 *
 *  Created on: Sep 5, 2020
 *      Author: OS1
 */

#include "ListSem.h"
#include "SCHEDULE.H"
ListSem::ListSem() {
	// TODO Auto-generated constructor stub
	first = last = 0;
	num=0;
}

void ListSem::timeDecrementAll(){
	Elem* pom = first;
	while(pom){
		pom->sem->listaBlokiranihNaSemaforu->timeDec();
		pom=pom->next;
	}
}

ListSem::~ListSem() {
	// TODO Auto-generated destructor stub
	Elem* pom = first;
		while(pom){
			first = first->next;
			delete pom;
			pom=first;
		}
		first = last = pom = 0;
}

void ListSem::add(KerSem* sem){
	Elem* novi = new Elem(sem);
	if(!first) first = last = novi;
	else last = last->next = novi;
	num++;
}



void ListSem::remove(KerSem* sem1){
	if(!first)return;
	Elem* pom=first,*k=first->next;
	if(!k && pom->sem==sem1){
		first=last=k=0;
	}
	else{
	while(k){
		if(k->sem==sem1){
			pom->next=k->next;
			pom=k;
			break;
		}
		k=k->next;
		if(k)pom=pom->next;
	}
	if(pom->sem!=sem1 && pom->next->sem==sem1){
		k=pom->next;
		last=pom;
		pom=k;
	}

	}

		while(pom->sem->listaBlokiranihNaSemaforu->num){//p1->sem->unlocki
			PCB* pom1 = pom->sem->listaBlokiranihNaSemaforu->get();
			//syncPrintf("Skinuo sam sa liste i sada ih ima %d\n",listaBlokiranihNaSemaforu->num);
			pom1->state = PCB::READY;
			Scheduler::put(pom1);
			pom->sem->semVal++;
		}
	//p1->sem->listaBlokiranihNaSemaforu->first = p1->sem->listaBlokiranihNaSemaforu->last=0;

	Global::listOfSemaphores->num--;
	delete pom;

}
