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

}

ListSem::~ListSem() {
	// TODO Auto-generated destructor stub
	emptyList();
}

void ListSem::add(KerSem* sem){
	Elem* novi = new Elem(sem);
	if(!first) first = last = novi;
	else last = last->next = novi;
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
	Elem* k = first, *pom=0;
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
	}
}
