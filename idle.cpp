/*
 * idle.cpp
 *
 *  Created on: Sep 2, 2020
 *      Author: OS1
 */

#include "idle.h"
extern int syncPrintf(const char *format, ...);
idle::idle(StackSize stackSize, Time timeSlice) {
	// TODO Auto-generated constructor stub
}

idle::~idle() {
	// TODO Auto-generated destructor stub
}

void idle::run(){
	while(1){
		syncPrintf(".");
	}
}
