/*
 * IVTEntry.h
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#define Nt 256
#include "KerEv.h"

typedef void interrupt (*pInterrupt)(...);
typedef unsigned char IVTNo;


#define PREPAREENTRY(numEntry,oldF)\
		void interrupt inter##numEntry(...);\
		IVTEntry newEntry##numEntry(numEntry,inter##numEntry);\
		void interrupt inter##numEntry(...){\
			newEntry##numEntry.signal();\
			if(oldF!=0)\
				newEntry##numEntry.old();\
		}



class IVTEntry {
public:
	friend class Event;
	friend class Semaphore;
	friend class KerEv;

	volatile static IVTEntry* table[Nt];

	void signal();
	IVTEntry(IVTNo ivtNo, pInterrupt pint);
	virtual ~IVTEntry();

	KerEv* myImpl;


	void old();
	static void dodaj(IVTNo ivtNo, KerEv* x);

	pInterrupt oldRout;
	IVTNo ivtNo;
};

#endif /* IVTENTRY_H_ */
