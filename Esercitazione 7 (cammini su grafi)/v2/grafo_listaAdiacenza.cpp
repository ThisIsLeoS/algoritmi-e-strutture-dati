#include "grafo_listaAdiacenza.h"

Grafo::Grafo()
{
	headV = NULL;
}

bool Grafo::camminoAciclico(string origine, string destinazione, int & distanza, ListaAdiacenza & l)
// costruisce un possibile cammino aciclico tra il nodo origine e quello destinazione come 
// var. di tipo ListaAdiacenza (parametro "l" passato per riferimento), calcola la distanza
// fra i due nodi (parametro "distanza" passato per riferimento) e restituisce "true". Se non esiste
// un cammino aciclico tra i due nodi, restitutisce "false"
// nota: la distanza totale potresti calcolarla dalla lista di adiacenza l, quindi potrebbero 
// esserci modi migliori rispetto al metterla nel parametro "distanza" passato per riferimento
{	
	if (origine == destinazione) return false; // se origine e destinazione coincidono, non c'è un
					           // cammino aciclico tra i due
	// con le prossime righe di codice si verifica che il nodo origine e quello destinazione
	// facciano entrambi parte del grafo. In caso contratrio, non c'è un cammino aciclico fra i due
	Vertex * nodoCorrente = cercaVertice(origine); // notare che il puntatore al nodo origine è
                                                       // salvato nella var. "nodoCorrente", che verrà
                                                       // passata alla f. "camminoAciclicoRic", se non
                                                       // si esce dall'attuale corpo prima della 
                                                       // chiamata
	if (nodoCorrente == NULL) return false;
	if ((cercaVertice(destinazione)) == NULL) return false;
	// con le prossime righe di codice, vengono smarcati tutti i nodi del grafo
	Vertex * vtxPtAux = headV;
	while (vtxPtAux != NULL)
	{
		vtxPtAux->mark = false;
		vtxPtAux = vtxPtAux->next;
	}
	return camminoAciclicoRic(origine, destinazione, nodoCorrente, distanza, l);
}

bool Grafo::camminoAciclicoRic(string origine, string destinazione, Vertex * nodoCorrente, int & distanza, ListaAdiacenza & l)
{
	nodoCorrente->mark = true; // si marca il nodo corrente
	if (nodoCorrente->info == destinazione) // se il nodo corrente è quello di destinazione
	{
		l.insert(0, nodoCorrente); // si inserisce nella lista di adiacenza (distanza 0, perchè non 
								   // c'è una prossima tappa del cammino aciclico)
		return true; // si restituisce true
	}
	// se il nodo corrente non è quello di destinazione
	Edge * cur = nodoCorrente->listaAd.head;
	while (cur!= NULL) // while per scorrere la lista di adiacenza del nodo corrente
	{
		if (cur->adiac->mark != true) // se il nodo adiacente al nodo corrente non è marcato
		{
			if (camminoAciclicoRic(origine, destinazione, cur->adiac, distanza, l)) // si fa
			// una chiamata ricorsiva e si valuta il valore di ritorno. Se restituisce true: 
			{
				l.insert(cur->info, nodoCorrente);	// si inserisce nella lista di adiacenza il 
				// nodoCorrente e la distanza rispetto al nodo che ha restituito true 
				// aggiunge al cammino l'arco tra il nodo corrente e "quello che ha restituto true"
				distanza += cur->info; // si aggiorna la distanza sommando quella dell'arco 
				// appena aggiunto (nota: la var. "distanza" inizialmente ha valore 0, quindi è ok 
				// il "+="
				return true; // si restituisce true
			}
		}
		cur = cur->next;
	}
	return false;
}

Vertex * Grafo::cercaVertice(string info)
// restituisce il puntatore al vertice "info", se questo fa parte del grafo, altrimenti restituisce 
// NULL
{
	Vertex * cur = headV;
	while (cur != NULL)
	{
		if (cur->info == info) return cur;
		cur = cur->next;
	}
	return NULL;
}

bool Grafo::sonoAdiacenti(string origine, string destinazione)
// restituiscce true se il vertice "destinazione" si trova nella lista di adiacenza del vertice 
// "origine", false altrimenti
{
	Vertex * auxV = cercaVertice(origine);
	return auxV->listaAd.search(destinazione);
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
	vtxPt1->listaAd.insert(distanza, vtxPt2);
	// è inserito il nodo origine nella lista di adiacenza del nodo destinazione
	vtxPt2->listaAd.insert(distanza, vtxPt1);
	return true;
}

bool Grafo::aggiungiVerticeIsolato(string info)
// se il nodo "info" non è presente nella lista dei nodi del grafo, lo aggiunge a quest'ultima e 
// restituisce true, altrimenti non lo aggiunge e restituisce false
{
	if (cercaVertice(info) != NULL) return false; // se il nodo è già presente
	ListaAdiacenza listaAd;	
	Vertex * aux = new Vertex;
	aux->info = info;
	aux->next = headV;
	aux->listaAd = listaAd;
	aux->mark = false;
	headV = aux;
	return true;
}

string Grafo::strToPrint()
// stampa a schermo la lista dei nodi e, per ogni nodo, la lista dei nodi ad esso adiacenti
{
	string str;
	ostringstream oStSt;
	Vertex * cur = headV; 
	int i = 1;
	while (cur != NULL)
	{
		oStSt << i;
		str += oStSt.str() + "° nodo: " + cur->info + "\n";
		oStSt.str("");
		str += "Nodi ad esso adiacenti: " + cur->listaAd.strToPrint() + "\n";
		cur = cur->next;
		i++;
	}
	return str;
}

ListaAdiacenza::ListaAdiacenza()
{
	head = NULL;
}

bool ListaAdiacenza::isEmpty()
{
	return head == NULL;
}

void ListaAdiacenza::insert(int distanza, Vertex * adiac)
// inserisce un nuovo arco in testa. I parametri passatile servono per riempire i campi del nuovo
// arco
{
	// è creato il nuovo arco da inserire
	Edge * edge = new Edge; 
	// sono inizializzati tutti i campi del nuovo arco ed è fatto l'inserimento in testa
	edge->info = distanza;
	edge->adiac = adiac; 
	edge->next = head;
	head = edge;
}

bool ListaAdiacenza::search(const string & destinazione)
// restituisce true se il nodo a cui appartiene la lista di adiacenza è adiacente al nodo di nome
// "destinazione"
{
	Edge * cur = head;
	while (cur != NULL)
	{
		if (cur->adiac->info == destinazione) return true; // se la var. di tipo Nodo puntata dal
		// campo "adiac" di un elem. della lista di adiacenza contiene "destinazione" nel campo
		// "info", è restituito true
		cur = cur->next;
	}
	return false;
}

string ListaAdiacenza::strToPrint()
// restituisce una stringa contenente i nomi di tutti i nodi adiacenti al nodo a cui la lista di
// adiacenza appartiene (restituisce "nessuno" se nn ce ne sono)
{
	string str;
	if (isEmpty()) return "nessuno";
	Edge * cur = head;
	while (cur != NULL)
	{
		str += cur->adiac->info + " ";
		cur = cur->next;
	}
	return str;
}
