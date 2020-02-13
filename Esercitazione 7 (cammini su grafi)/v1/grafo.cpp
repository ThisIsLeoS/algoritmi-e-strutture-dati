#include "grafo.h"

Grafo::Grafo()
{
	headV = NULL;
}

bool Grafo::camminoAciclico(string origine, string destinazione, int & distanza, Grafo & g1)
// costruisce un possibile cammino aciclico tra il nodo origine e quello destinazione come 
// var. di tipo grafo (parametro "g1" passato per riferimento), calcola la distanza
// fra i due nodi (parametro "distanza" passato per riferimento) e restituisce "true". Se non esiste
// un cammino aciclico tra i due nodi, restitutisce "false"
{	
	if (origine == destinazione) return false; // se origine e destinazione coincidono, non c'è un
											   // cammino aciclico tra i due
	// con le prossime quattro righe di codice si verifica che il nodo origine e quello destinazione
	// facciano entrambi parte del grafo. In caso contratrio, non c'è un cammino aciclico fra i due
	Vertex * nodoCorrente = cercaVertice(origine); // notare che il puntatore al nodo origine è
												   // salvato nella var. "nodoCorrente", che verrà
												   // passata alla f. "camminoAciclicoRic", se non
												   // si esce dall'attuale corpo prima della 
												   // chiamata
	if (nodoCorrente == NULL) return false;
	if ((cercaVertice(destinazione)) == NULL) return false;
	// con le prossime sei righe di codice, vengono smarcati tutti i nodi del grafo
	Vertex * vtxPtAux = headV;
	while (vtxPtAux != NULL)
	{
		vtxPtAux->mark = false;
		vtxPtAux = vtxPtAux->next;
	}
	return camminoAciclicoRic(origine, destinazione, nodoCorrente, distanza, g1);
}

bool Grafo::camminoAciclicoRic(string origine, string destinazione, Vertex * nodoCorrente, int & distanza, Grafo & g1)
{
	nodoCorrente->mark = true; // si marca il nodo corrente
	if (nodoCorrente->info == destinazione) // se il nodo corrente è quello di destinazione
	{
		g1.aggiungiVerticeIsolato(nodoCorrente->info); // si aggiunge il nodo al cammino
		return true; // si restituisce true
	}
	// se il nodo corrente non è quello di destinazione
	Edge * edgPtCur = nodoCorrente->headE; // cursore per scorrere la lista di adiacenza del nodo
										   // corrente
	while (edgPtCur != NULL) // while per scorrere la lista di adiacenza del nodo corrente
	{
		if (edgPtCur->adiac->mark != true) // se il nodo adiacente al nodo corrente non è marcato
		{
			if (camminoAciclicoRic(origine, destinazione, edgPtCur->adiac, distanza, g1)) // si fa
			// una chiamata ricorsiva e si valuta il valore di ritorno. Se restituisce true: 
			{
				g1.aggiungiVerticeIsolato(nodoCorrente->info); // si aggiunge il nodo al cammino
				// nota: questa chiamata va prima della successiva, altrimenti il nodo origine a cui
				// aggiungere l'arco non è presente nel grafo
				g1.aggiungiArco(nodoCorrente->info, edgPtCur->adiac->info, edgPtCur->info);	// si 
				// aggiunge al cammino l'arco tra il nodo corrente e "quello che ha restituto true"
				distanza += edgPtCur->info; // si aggiorna la distanza sommando quella dell'arco 
				// appena aggiunto (nota: la var. "distanza" inizialmente ha valore 0, quindi è ok 
				// il "+="
				return true; // si restituisce true
			}
		}
		edgPtCur = edgPtCur->next;
	}
	return false;
}

Vertex * Grafo::cercaVertice(string info)
// restituisce il puntatore al vertice "info", se questo fa parte del grafo, altrimenti restituisce 
// NULL
{
	Vertex* aux = headV;
	while (aux != NULL)
	{
		if (aux->info == info) return aux;
		aux = aux->next;
	}
	return NULL;
}

bool Grafo::sonoAdiacenti(string origine, string destinazione)
// restituiscce true se il vertice "destinazione" si trova nella lista di adiacenza del vertice 
// "origine", false altrimenti
{
	Vertex * auxV = cercaVertice(origine);
	Edge * auxE = auxV->headE;
	while (auxE != NULL)
	{
		if (auxE->adiac->info == destinazione) return true;
		auxE = auxE->next;
	}
	return false;
}

bool Grafo::aggiungiArco(string origine, string destinazione, int distanza)
// se i nodi "destinazione" e "origine" fanno parte del grafo e non sono già adiacenti, aggiunge il 
// nodo "destinazione" nella lista di adiacenza del nodo "origine" e viceversa e restituisce true, 
// altrimenti restituisce false
{
	// con le prossime cinque righe di codice si verifica che i nodi "destinazione" e "origine" 
	// facciano parte del grafo e che non siano già adiacenti. 	
	Vertex * vtxPt1 = cercaVertice(origine);
	if (vtxPt1 == NULL) return false;
	Vertex * vtxPt2 = cercaVertice(destinazione);
	if (vtxPt2 == NULL) return false;
	if (sonoAdiacenti(origine, destinazione)) return false;
	// è inserito il nodo destinazione nella lista di adiacenza del nodo origine
	Edge * edgPt = new Edge;
	edgPt->info = distanza;
	edgPt->next = vtxPt1->headE;
	edgPt->adiac = vtxPt2; 
	vtxPt1->headE = edgPt;
	// è inserito il nodo origine nella lista di adiacenza del nodo destinazione
	edgPt = new Edge;
	edgPt->info = distanza;
	edgPt->next = vtxPt2->headE;
	edgPt->adiac = vtxPt1; 
	vtxPt2->headE = edgPt;
	return true;
}

bool Grafo::aggiungiVerticeIsolato(string info)
// se il nodo "info" non è presente nella lista dei nodi del grafo, lo aggiunge a quest'ultima e 
// restituisce true, altrimenti non lo aggiunge e restituisce false
{
	if (cercaVertice(info) != NULL) return false; // se il nodo è già presente
	Vertex * aux = new Vertex;
	aux->info = info;
	aux->next = headV;
	aux->headE = NULL;
	aux->mark = false;
	headV = aux;
	return true;
}

void Grafo::stampa()
// stampa a schermo la lista dei nodi e, per ogni nodo, la lista dei nodi ad esso adiacenti
{
	Vertex * aux1 = headV;
	Edge * aux2; 
	int i = 1;
	while (aux1 != NULL)
	{
		cout << i << "° nodo: " << aux1->info << endl;
		aux2 = aux1->headE;
		cout << "Nodi ad esso adiacenti: ";
		if (aux2 == NULL) cout << "nessuno\n";
		else
		{
			while (aux2 != NULL)
			{
				cout << aux2->adiac->info << " ";
				aux2 = aux2->next;
			}
		}
		cout << endl; // fuori dallo "if/else" perchè bisgna andare a capo in entrambi i casi
		aux1 = aux1->next;
		i++;
	}
}
