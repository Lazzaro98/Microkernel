/*
 * Global.h
 *
 *  Created on: Aug 29, 2020
 *      Author: OS1
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "Thread.h"
#include "PCB.h"


class Global {
private:
	volatile static int lockFlag;
public:
	friend class PCB;
	friend class ListThr;
	friend class Semaphore;
	friend class ListSem;

	volatile static int zahtevana_promena_konteksta;
	volatile static PCB* running;
	volatile static ListThr* listOfThreads;
	volatile static PCB* Global::idleTr;
	volatile static ListSem* listOfSemaphores;
	static void lock();
	static void unlock();

	static void dodaj(Thread* thread);
	Global();
	virtual ~Global();
};

#endif /* GLOBAL_H_ */
