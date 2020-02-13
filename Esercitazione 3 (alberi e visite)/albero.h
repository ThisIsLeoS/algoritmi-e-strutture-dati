#ifndef ALBERO_H
#define ALBERO_H

#include "queue.h" // per la f. bfs e perchè viene usato anche in questo modulo il tipo Nodo
#include <iostream> // per la f. bfs

using namespace std;

#define DEBUGa

struct Albero
{
	Albero();
	bool isEmpty();
	bool affiliazione(const string &, const string &); 
	string bfs();
	private:
		Nodo* tree;
		// le seguenti f. sono private perchè di supporto alla f. affiliazione
		Nodo* checkPadre(const string &);
		bool checkFiglio(const string &);
};

#endif
