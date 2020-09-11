/*
 * PCB.h
 *
 *  Created on: Aug 29, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "Thread.h"
#include "Global.h"
#include "ListPCB.h"



class PCB {
public:
	friend class Thread;
	friend class Global;
	friend class ListThr;

	typedef enum State {CREATED, READY, BLOCKED, FINISHED} State;

	static ListThr* listOfThreads;
	volatile static unsigned int brojac;
	int blkFlag;
	static void interrupt timer();
	static void dispatch();
	void createProcess();
	static void wrapper();
	PCB(Time timeSlice1, Thread* myThread1, StackSize stackSize1);
	virtual ~PCB();
protected:

public:
	unsigned ss;
	unsigned sp;
	unsigned bp;
	unsigned *stack;
	ID id;
	Thread *myThread;
	StackSize stackSize;
	State state;
	Time timeSlice;
	ListPCB *listBlokiranih;

	ID getId();

};

#endif /* PCB_H_ */
