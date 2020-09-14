/*
 * KerSem.h
 *
 *  Created on: Sep 5, 2020
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

#include "Queue.h"


typedef unsigned int Time;

class KerSem {
private:
public:

	friend class Sem;

	friend class ListSem;

	Sem *sem;
	int semVal;


	Queue* listaBlokiranihNaSemaforu;
	int wait(Time maxTimeToWait);
	int signal(int n=1);
	KerSem(int init, Sem *sem1);
	virtual ~KerSem();

	void block(Time timeToWait1);
	void unblock();
};

#endif /* KERSEM_H_ */
