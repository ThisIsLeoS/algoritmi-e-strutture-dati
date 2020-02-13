#ifndef IMPIEGATO_H
#define IMPIEGATO_H

#include <string> // per la dichiarazione e l'uso di var. di tipo string
#include <sstream> // per la f. print_impiegato
#include <iostream> // per i "cerr" di debug

#define DEBUG

using namespace std; // per l'uso della keyword string

enum Confronto
{
	maggiore, minore, uguale
};

struct Impiegato
{
	// metodi per leggere dalle istanze private	
	string readNome();
	string readCognome();
	int readAnnoAssunzione();

	// metodi per scrivere nelle istanze private
	void writeNome(const string &);
	void writeCognome(const string &);
	void writeAnnoAssunzione(const int &);
	
	string printImp(); // restituisce una stringa contenente i campi identificativi di un impiegato
	Confronto orderImp(const Impiegato &); /* "dice" se l'impiegato passato è maggiore di, minore 
										   di o uguale a quello considerato secondo l'ordine 
										   lessicografico */
	private:	
		string nome, cognome;
		int annoAssunzione;
};

#endif
