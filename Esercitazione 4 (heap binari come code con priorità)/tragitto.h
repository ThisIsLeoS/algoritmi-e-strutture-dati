#ifndef TRAGITTO_H
#define TRAGITTO_H

#include <vector> // per l'istanza di Tragitto e altro
#include <string> // per la var. citta'

using namespace std;

struct Tappa
{
	string citta; // il mio compilatore non accetta il carattere "à" nel nome di una var., credo
				  // perchè la tabella ASCII sul mio pc non lo comprenda
	float distPrev; // distanza dalla precedente città visitata
};

struct Tragitto
{
	Tragitto();
	void enqueue(const Tappa &);
	void dequeue(); // da ricordarsi che va chiamata isEmpty prima 
	Tappa first(); // da ricordarsi che va chiamata isEmpty prima 
	bool isEmpty();
	private:
		vector <Tappa> tr;
};

#endif
