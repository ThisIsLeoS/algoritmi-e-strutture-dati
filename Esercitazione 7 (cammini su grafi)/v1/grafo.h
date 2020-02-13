#ifndef GRAFO_H
#define GRAFO_H

using namespace std;

#include <string> // per le f. "aggiungiVerticeIsolato" e "cercaVertice"
#include <iostream> // per la f. "stampa"

struct Edge;

struct Vertex
{
	string info; // il nome della città	
	Vertex * next;
	Edge * headE;
	bool mark; // serve per la f. "camminoAciclico"
};

struct Edge
{
	int info; // è la distanza fra due città	
	Edge * next;
	Vertex * adiac;
};

struct Grafo
{
	Grafo();
	bool aggiungiVerticeIsolato(string);
	bool aggiungiArco(string, string, int);
	bool sonoAdiacenti(string, string);
	void stampa();
	bool camminoAciclico(string, string, int &, Grafo &);
	private:
		bool camminoAciclicoRic(string, string, Vertex *, int &, Grafo &); // di supporto alla
		// "camminoAciclico"
		Vertex * cercaVertice(string); // di supporto alla "aggiungiVerticeIsolato", alla 
		// "sonoAdiacenti", alla "aggiungiArco", alla "camminoAciclico"
		Vertex * headV;
};

#endif
