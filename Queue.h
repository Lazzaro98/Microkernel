/*
 * Queue.h
 *
 *  Created on: Sep 3, 2020
 *      Author: OS1
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "PCB.h"

class Queue {
public:
	friend class PCB;

	struct Elem{
		PCB* pcb;
		Elem* next;
		Time timeToWait;
		Elem(PCB* pcb1,Time timeToWait1){
			pcb=pcb1;
			timeToWait=timeToWait1;
			next = 0;
		}
	};
	Elem *first, *last;
	int num;

	void put(PCB* pcb, Time time);
	PCB* get();
	void emptyList();
	void timeDec();

	Queue();
	virtual ~Queue();
};

#endif /* QUEUE_H_ */
