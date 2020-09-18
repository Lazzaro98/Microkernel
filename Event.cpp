/*
 * Event.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */

#include "Event.h"

Event::Event(IVTNo ivtNo) {
	// TODO Auto-generated constructor stub
	Global::lock();
	myImpl = new KerEv(ivtNo);
	Global::unlock();
}

Event::~Event() {
	// TODO Auto-generated destructor stub
	delete myImpl;
	myImpl=0;
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}
