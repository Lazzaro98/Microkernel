/*
 * Sem.h
 *
 *  Created on: Sep 11, 2020
 *      Author: OS1
 */

#ifndef SEM_H_
#define SEM_H_

#include "KerSem.h"
class Sem {
public:
	friend class KerSem;

	Sem(int init=1);
	virtual ~Sem();
	void decQueue();
	int wait(Time maxTimeToWait);
	int signal(int n=1);
	int val() const;
private:
	KerSem* myImpl;
};

#endif /* SEM_H_ */
