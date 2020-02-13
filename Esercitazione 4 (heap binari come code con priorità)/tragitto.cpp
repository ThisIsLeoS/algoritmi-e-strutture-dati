#include "tragitto.h"

Tragitto::Tragitto()
{
	tr.resize(0);
}

void Tragitto::enqueue(const Tappa & newTappa)
{
	tr.push_back(newTappa);
}
	
void Tragitto::dequeue() // da ricordarsi che va chiamata isEmpty prima
{
	tr.erase(tr.begin());
}

Tappa Tragitto::first() // da ricordarsi che va chiamata isEmpty prima
{
	return tr.front();
}
	
bool Tragitto::isEmpty()
{
	return tr.empty();
}
