/*
 * Event.h
 *
 *  Created on: Sep 15, 2020
 *      Author: OS1
 */

// File: event.h
#ifndef _event_h_
#define _event_h_
#include "KerEv.h";
typedef unsigned char IVTNo;

class KerEv;

class Event {
	public:
		Event (IVTNo ivtNo);
		~Event ();
		void wait ();
	protected:
		friend class KernelEv;
		void signal(); // can call KernelEv
	private:
		KerEv* myImpl;
	};
#endif
