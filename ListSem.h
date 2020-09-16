/*
 * ListSem.h
 *
 *  Created on: Sep 5, 2020
 *      Author: OS1
 */

#ifndef LISTSEM_H_
#define LISTSEM_H_

#include "KerSem.h"

class ListSem {
public:
	int num;
	struct Elem {
		KerSem* sem;
		Elem* next;
		Elem(KerSem* sem1, Elem* next1=0){
			sem=sem1;
			next=next1;
		}
	};
	Elem *first, *last;

	void add(KerSem* sem);
	KerSem* get();
	void emptyList();
	void timeDecrementAll();
	void remove(KerSem* SemToRemove);

	ListSem();
	virtual ~ListSem();
};

#endif /* LISTSEM_H_ */
