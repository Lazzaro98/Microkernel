/*
 * Sem.cpp
 *
 *  Created on: Sep 11, 2020
 *      Author: OS1
 */

#include "Sem.h"

Sem::Sem(int init) {
	// TODO Auto-generated constructor stub
	myImpl = new KerSem(init,this);
}

Sem::~Sem() {
	// TODO Auto-generated destructor stub
	delete myImpl;
	myImpl=0;
}

void Sem::decQueue(){
	myImpl->listaBlokiranihNaSemaforu->timeDec();
}

int Sem::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}

int Sem::signal(int n){
	return myImpl->signal(n);
}

int Sem::val() const {
	return myImpl->semVal;
}
