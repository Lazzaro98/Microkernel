/*
 * Semaphor.h
 *
 *  Created on: Sep 18, 2020
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

#include "KerSem.h"
class Semaphore {
public:
	friend class KerSem;

	void decQueue();
	int wait(Time maxTimeToWait);
	int signal(int n=1);
	int val() const;
	void setTestId(int id1);
	Semaphore(int init=1);
	virtual ~Semaphore();
private:
	KerSem* myImpl;
};

#endif /* SEMAPHOR_H_ */
