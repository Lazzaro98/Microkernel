/*
 * IVTEntry.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */

#include "IVTEntry.h"
#include<dos.h>
#include "Global.h"
#include "KerEv.h"

volatile IVTEntry* IVTEntry::table[num]={0};

IVTEntry::IVTEntry(IVTNo ivtNo1,pInterrupt pint1) {
	// TODO Auto-generated constructor stub
	ivtNo=ivtNo1;
	myImpl=0;
	Global::lock();
#ifndef BCC_BLOCK_IGNORE
	oldRoutine = getvect(ivtNo);
	setvect(ivtNo,pint1);
#endif
	Global::unlock();
	IVTEntry::table[ivtNo]=this;
	//dodaj(ivtNo,);
}

IVTEntry::~IVTEntry() {
	// TODO Auto-generated destructor stub
	Global::lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo,oldRoutine);
#endif
	Global::unlock();
	delete myImpl;
	myImpl=0;
	oldRoutine=0;
}

void IVTEntry::signal(){
	this->myImpl->signal();
}

void IVTEntry::callOld(){
	oldRoutine();
}

void IVTEntry::dodaj(IVTNo ivtNo, KerEv* x){
	//table[ivtNo]->myImpl=x;
}
