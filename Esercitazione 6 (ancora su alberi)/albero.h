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
	int grado(Nodo *);
	bool affiliazione(const string &, const string &, int &);
	bool erase(const string &, int &);
	string bfs(); // adattata rispetto a quella dell'es. 3 per produrre la visualizzazione 
				  // strutturata
	bool minCommonAncestor(const string &, const string &, string &);
	private:
		Nodo* tree;
		Nodo* checkPadre(const string &); // di supporto alla funzione affiliazione e ad altre
		bool checkFiglio(const string &); // di supporto alla f. affiliazione
};

#endif
