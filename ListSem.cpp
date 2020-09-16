/*
 * ListSem.cpp
 *
 *  Created on: Sep 5, 2020
 *      Author: OS1
 */

#include "ListSem.h"

ListSem::ListSem() {
	// TODO Auto-generated constructor stub
	first = last = 0;
	num=0;
}

ListSem::~ListSem() {
	// TODO Auto-generated destructor stub
	emptyList();
}

void ListSem::add(KerSem* sem){
	Elem* novi = new Elem(sem);
	if(!first) first = last = novi;
	else last = last->next = novi;
	num++;
}

void ListSem::timeDecrementAll(){
	Elem* pom = first;
	while(pom){
		pom->sem->listaBlokiranihNaSemaforu->timeDec();
		pom=pom->next;
	}
}

void ListSem::emptyList(){
	Elem* pom = first;
	while(pom){
		first = first->next;
		delete pom;
		pom=pom->next;
	}
	first = last = pom = 0;
}

void ListSem::remove(KerSem* sem1){
	/*Elem* k = first, *pom=0;
	while(k){
		if(k->sem==sem1){
				if(k==first){
				first = last = 0;
				delete k;
				}
			else {
				pom->next = k->next;
				delete k;
				pom = k;
				k=k->next;
			}
		}
	}*/

	ListSem::Elem* p1 = first, *p2=0;
	while(p1 && p1->sem != sem1){
		p2=p1;
		p1=p1->next;
	}
	if(p1==0)return;

	if(p1==first)
		first=first->next;
	else if (p1==last)
		last=p2;
	else
		p2->next=p1->next;

	if(p1->sem->listaBlokiranihNaSemaforu->num){
		while(p1->sem->listaBlokiranihNaSemaforu->num){
			p1->sem->unblock();
			p1->sem->semVal++;
		}
	}
	p1->sem->listaBlokiranihNaSemaforu->first = p1->sem->listaBlokiranihNaSemaforu->last=0;

	Global::listOfSemaphores->num--;
	delete p1;

}
