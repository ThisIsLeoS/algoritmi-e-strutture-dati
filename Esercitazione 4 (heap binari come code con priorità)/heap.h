#ifndef HEAP_H
#define HEAP_H

#include "evento.h" // per Evento e altro

#define length 20 // numero di celle dell'array "hArray"

struct Heap
{
	Heap();
	bool isEmpty();
	bool findMin(Evento &);
	bool deleteMin();
	void insert(Evento);
	private:
		int n; // numero di elementi presenti nell'array "hArray"
		Evento hArray[length];
		void muoviBasso(int); // di supporto alla f. deleteMin
		void muoviAlto(int); // di supporto alla f. insert
		int minTimestamp(int, int); // di supporto alla f. muoviBasso
};

#endif
