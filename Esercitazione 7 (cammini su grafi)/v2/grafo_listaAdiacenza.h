#ifndef GRAFO_LISTAADIACENZA_H
#define GRAFO_LISTAADIACENZA_H

using namespace std;

#include <string> // per le f. "aggiungiVerticeIsolato" e "cercaVertice"
#include <sstream> // per la f. "strToPrint"

struct Vertex;

struct Edge
{
	int info; // è la distanza fra due città	
	Edge * next;
	Vertex * adiac;
};

struct ListaAdiacenza
{
	ListaAdiacenza();
	bool isEmpty();
	void insert(int, Vertex *);
	bool search(const string &);
	string strToPrint();
	Edge * head; // nella f. "camminoAciclico" serve accedere direttamente a head, che quindi non è
				 // privata. Il principio di incapsulamento è cmq rispettato per il grafo, le cui
				 // liste di adiacenza nn possono essere accedute dal main
};

struct Vertex
{
	string info; // il nome della città	
	Vertex * next;
	ListaAdiacenza listaAd;
	bool mark; // serve per la f. "camminoAciclico"
};

struct Grafo
{
	Grafo();
	bool aggiungiVerticeIsolato(string);
	bool aggiungiArco(string, string, int);
	bool sonoAdiacenti(string, string);
	string strToPrint();
	bool camminoAciclico(string, string, int &, ListaAdiacenza &);
	private:
		bool camminoAciclicoRic(string, string, Vertex *, int &, ListaAdiacenza &); // di supporto alla
		// "camminoAciclico"
		Vertex * cercaVertice(string); // di supporto alla "aggiungiVerticeIsolato", alla 
		// "sonoAdiacenti", alla "aggiungiArco", alla "camminoAciclico"
		Vertex * headV;
};

#endif
