#ifndef BST_H
#define BST_H

#include "impiegato.h" // serve per Impiegato, per Confronto e altro 

struct NodoBST
{
	Impiegato imp;
	NodoBST * figlioSx, * figlioDx, * padre;
};

struct BST
{
	BST();	
	string DFSSimmetrica(); /* restituisce una stringa contenente i campi identificativi di ogni
							impiegato (nome, cognome, anno assunzione). I campi di un impiegato si
							trovano prima o dopo quelli di un altro a seconda della relazione
							d'ordine stabilita nella orderImp (vd. impiegato.cpp) */ 
	bool insert(const Impiegato &);
	NodoBST* search(const Impiegato &);
	bool erase(Impiegato);
	private:
		NodoBST* tree; // istanza della struct (puntatore alla radice)
		NodoBST* searchPadre(const Impiegato &); // di supporto alla insert
		void DFSSimmetricaAux(NodoBST*, string &); // di supporto alla DFSSimmetrica
		// bool insertAux(Impiegato, NodoBST* &); // di supporto alla insert ricorsiva (vd. il .cpp)
		NodoBST* searchMax(NodoBST*); // di supporto alla erase
};

#endif
