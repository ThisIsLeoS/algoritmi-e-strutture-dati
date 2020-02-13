#include "queue.h"

Queue::Queue()
{
	puntNodi.resize(0);
}

void Queue::enqueue(Nodo* & newNodo)
{
	puntNodi.push_back(newNodo);
}
	
void Queue::dequeue() // da ricordarsi che va chiamata isEmpty prima
{
	puntNodi.erase(puntNodi.begin());
}

Nodo* Queue::first() // da ricordarsi che va chiamata isEmpty prima
{
	return puntNodi.front();
}
	
bool Queue::isEmpty()
{
	return puntNodi.empty();
}
