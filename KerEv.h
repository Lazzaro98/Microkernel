/*
 * KerEv.h
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */

#ifndef KEREV_H_
#define KEREV_H_
#include "IVTEntry.h"
#include "Thread.h"
#include"PCB.h"

typedef unsigned char IVTNo;

class KerEv {
public:
	IVTNo entrynum;
	int evVal;
	PCB* blocked;
	PCB* myThread;

	friend class IVTEntry;

	void wait();
	void signal();
	KerEv(IVTNo ivtNo);
	virtual ~KerEv();
};

#endif /* KEREV_H_ */
