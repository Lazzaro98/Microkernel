/*
 * ListThr.h
 *
 *  Created on: Aug 30, 2020
 *      Author: OS1
 */

#ifndef LISTTHR_H_
#define LISTTHR_H_

#include "Thread.h"

class ListThr {
public:

friend class Thread;

struct Elem {
public:
	Thread* thread;
	Elem* next;
	Elem(Thread* thread1, Elem* next1 = 0){
			this->thread = thread1;
			this->next = next1;
		}
	};

	Elem *first, *last;

	void add(Thread* thread1);
	static Thread* getThreadById(ID id);


	ListThr();
	virtual ~ListThr();
};

#endif /* LISTTHR_H_ */
