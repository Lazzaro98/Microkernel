/*
 * Event.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */

#include "Event.h"

Event::Event(IVTNo ivtNo) {
	// TODO Auto-generated constructor stub
	myImpl = new KerEv(ivtNo);
}

Event::~Event() {
	// TODO Auto-generated destructor stub
	myImpl=0;
	delete myImpl;
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}
