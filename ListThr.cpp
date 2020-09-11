/*
 * ListThr.cpp
 *
 *  Created on: Aug 30, 2020
 *      Author: OS1
 */

#include "ListThr.h"
#include "PCB.h"
#include "Thread.h"
#include "Global.h"

ListThr::ListThr() {
	first = 0;
	last = 0;
}

ListThr::~ListThr() {
	// TODO Auto-generated destructor stub
	Elem* tek;

	while(first!=0){
		tek = first;
		first = first->next;
		tek->thread = 0;
		delete tek;
	}
	first = last = 0;
}

void ListThr::add(Thread* thread1){
	Elem* novi = new Elem(thread1);
	if(first == 0)
		first = last = novi;
	else
		last = last->next = novi;
}

Thread* ListThr::getThreadById(ID id1){
	Elem* tek = Global::listOfThreads->first;
	while (tek && tek->thread->myPCB->id != id1)
		tek=tek->next;
	if(tek)
		return tek->thread;
	else
		return 0;

}

