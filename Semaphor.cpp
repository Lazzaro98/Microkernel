/*
 * Semaphor.cpp
 *
 *  Created on: Sep 18, 2020
 *      Author: OS1
 */

#include "Semaphor.h"

Semaphore::Semaphore(int init) {
	// TODO Auto-generated constructor stub
	Global::lock();
	myImpl = new KerSem(init,this);
	Global::unlock();
}

Semaphore::~Semaphore() {
	// TODO Auto-generated destructor stub
	delete myImpl;
	myImpl=0;
}

void Semaphore::decQueue(){
	myImpl->listaBlokiranihNaSemaforu->timeDec();
}


int Semaphore::wait(Time maxTimeToWait){
	Global::lock();
	return myImpl->wait(maxTimeToWait);
	Global::unlock();
}

int Semaphore::signal(int n){
	Global::lock();
	return myImpl->signal(n);
	Global::unlock();
}

int Semaphore::val() const {
	return myImpl->semVal;
}

void Semaphore::setTestId(int id1){
	this->myImpl->setTestId(id1);
}
