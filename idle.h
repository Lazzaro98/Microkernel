/*
 * idle.h
 *
 *  Created on: Sep 2, 2020
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "Thread.h"

class idle : public Thread {
public:

	virtual void run();

	idle(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual ~idle();
};

#endif /* IDLE_H_ */
