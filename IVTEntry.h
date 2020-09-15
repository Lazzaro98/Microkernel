/*
 * IVTEntry.h
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "KerEv.h"

typedef unsigned char IVTNo;

#define PREPAREENTRY(numEntry,callOldF)\
		void interrupt inter##numEntry(...);\
		IVTEntry newEntry##numEntry(numEntry,inter##numEntry);\
		void interrupt inter##numEntry(...){\
			newEntry##numEntry.signal();\
			if(callOldF!=0)\
				newEntry##numEntry.callOld();\
		}

#define num 256

typedef void interrupt (*pInterrupt)(...);

class IVTEntry {
public:


	friend class Event;
	friend class KerEv;

	KerEv* myImpl;

	void signal();
	void callOld();
	IVTEntry(IVTNo ivtNo, pInterrupt pint);
	virtual ~IVTEntry();

	static void dodaj(IVTNo ivtNo, KerEv* x);
	volatile static IVTEntry* table[num];
private:

	IVTNo ivtNo;

	pInterrupt oldRoutine;
};

#endif /* IVTENTRY_H_ */
