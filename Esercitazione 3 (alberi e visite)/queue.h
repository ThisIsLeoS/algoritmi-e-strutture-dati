#ifndef QUEUE_H
#define QUEUE_H

#include <vector> // per l'istanza di Queue
#include <string> // per Nodo

using namespace std;

struct Nodo
{
	Nodo* primoFiglio;
	Nodo* fratelloDx;
	string info;
};

struct Queue
{
	Queue();
	void enqueue(Nodo* &);
	void dequeue(); // da ricordarsi che va chiamata isEmpty prima 
	Nodo* first(); // da ricordarsi che va chiamata isEmpty prima 
	bool isEmpty();
	private:
		vector <Nodo*> puntNodi;
};

#endif
