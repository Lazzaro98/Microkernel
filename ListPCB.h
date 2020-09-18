/*
 * ListPCB.h
 *
 *  Created on: Sep 4, 2020
 *      Author: OS1
 */

#ifndef LISTPCB_H_
#define LISTPCB_H_

class ListPCB {
public:

	friend class PCB;

	struct Elem{
		PCB* pcb;
		Elem* next;
		Elem(PCB* pcb1){
			pcb=pcb1;
			next=0;
		}
	};
	Elem *first,*last;
	void add(PCB* pcb);
	PCB* get();
	void listDel();
	void oslobodiBlokirane();
	void ispisiListu();
	ListPCB();
	virtual ~ListPCB();
};

#endif /* LISTPCB_H_ */
