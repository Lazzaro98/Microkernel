//#include "kernel.h"
#include <iostream.h>
#include <stdlib.h>
#include "Sem.h"
#include "Global.h"
#include "PCB.h"

/*
 	 Test: Semafori bez realizacije spavanja, deo javnog testa
*/

const int n = 10;
int count = 100;
Sem mutex(1);
extern int syncPrintf(const char *format, ...);
int mutex_glb = 1;

void mutex_glb_wait(){
 sloop:asm{
	mov ax, 0
	xchg ax, mutex_glb
}
 if(_AX ==0){
	PCB::dispatch();
	asm jmp sloop;
 }
}


#define intLock mutex_glb_wait();
#define intUnlock mutex_glb = 1;

static unsigned long next = 1;
/* RAND_MAX assumed to be 32767 */
int rand(void) {
    next = next * 1103515245 + 12345;
    return((unsigned)(next/65536) % 32768);
}
void srand(unsigned seed) {
    next = seed;
}


class BoundedBuffer {
public:

	BoundedBuffer (unsigned size);
	virtual ~BoundedBuffer ();
	int append (char);
	char take ();
	int  fullCount(){return itemAvailable.val();};    // potrebno consumeru

private:
	unsigned Size;
	Sem mutexa, mutext;
	Sem spaceAvailable, itemAvailable;
	char* buffer;
	int head, tail;
};

BoundedBuffer::BoundedBuffer (unsigned size) : Size(size),
	mutexa(1), mutext(1), spaceAvailable(size), itemAvailable(0),
	head(0), tail(0) {
		buffer = new char[size];
		if (!buffer) return;
	}

BoundedBuffer::~BoundedBuffer(){
	intLock
	delete [] buffer;
	intUnlock
}

int BoundedBuffer::append (char d) {
	spaceAvailable.wait(0);
	mutexa.wait(0);
		buffer[tail] = d;
		tail = (tail+1)%Size;
	mutexa.signal();
	itemAvailable.signal();
	return 0;
}

char BoundedBuffer::take () {
	itemAvailable.wait(0);
	mutext.wait(0);
		char d = buffer[head];
		head = (head+1)%Size;
	mutext.signal();
	spaceAvailable.signal();
	return d;
}

BoundedBuffer buffer(n/2);

class Producer: public Thread
{
public:
	Producer(): Thread() {};
	~Producer()
	{
		waitToComplete();
		syncPrintf("Zavrsio sam Producer-a.\n");
	}

protected:
	void run()
	{
		char c;
		while(count>0)
		{
			c = 65+(rand()%25);
			buffer.append(c);
			syncPrintf("%d. Producer %d puts '%c'\n",count,Thread::getRunningId(),c);
			//syncPrintf("Vrednost mutex-a je %d. ",mutex.val());
			mutex.wait(0);
			//syncPrintf("Vrednost mutex-a je %d. ",mutex.val());
			count--;
			mutex.signal();
			//syncPrintf("Vrednost mutex-a je %d.\n",mutex.val());
		}

	}
};

class Consumer: public Thread
{
public:
	Consumer(): Thread() {};
	~Consumer()
	{
		waitToComplete();
		syncPrintf("Zavrsio sam Consumera.\n");
	}

protected:
	void run()
	{
		char c;
		while(count>0)
		{

			c = buffer.take();
			syncPrintf("%d. Consumer %d gets '%c'\n",count,Thread::getRunningId(),c);
			//if(count==1) syncPrintf("Consumer je stigao do 0");
			mutex.wait(0);
			count--;
			mutex.signal();
		}

	}
};

void tick(){}

int userMain(int argc, char** argv)
{
	syncPrintf("Test starts.\n");
	Producer p;
	Consumer c;
	p.start();
	c.start();
	syncPrintf("Test ends.\n");
	return 0;
}


