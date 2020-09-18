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

volatile IVTEntry* IVTEntry::table[Nt]={0};

IVTEntry::IVTEntry(IVTNo ivtNo1,pInterrupt pint1) {
	// TODO Auto-generated constructor stub
	Global::lock();
#ifndef BCC_BLOCK_IGNORE
	ivtNo=ivtNo1;
	myImpl=0;
	oldRout = getvect(ivtNo);
	setvect(ivtNo,pint1);
	IVTEntry::table[ivtNo]=this;
#endif
	Global::unlock();
	//dodaj(ivtNo,);
}


void IVTEntry::signal(){
	this->myImpl->signal();
}

void IVTEntry::old(){
	oldRout();
}

void IVTEntry::dodaj(IVTNo ivtNo, KerEv* x){
	//table[ivtNo]->myImpl=x;
}

IVTEntry::~IVTEntry() {
	// TODO Auto-generated destructor stub
	Global::lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo,oldRout);
#endif
	Global::unlock();
	delete myImpl;
	myImpl=0;
	oldRout=0;
}
