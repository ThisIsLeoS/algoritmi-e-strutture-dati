#include "albero.h"

Albero::Albero()
{
	#ifdef DEBUG
	cerr << "Albero in\n";
	#endif
	tree=NULL;
	#ifdef DEBUG
	cerr << "Albero out\n";
	#endif
}

bool Albero::isEmpty()
{
	#ifdef DEBUG
	cerr << "isEmpty in\n";
	#endif
	#ifdef DEBUG
	cerr << "isEmpty out\n";
	#endif
	return tree==NULL;
}

bool Albero::affiliazione(const string & padre, const string & figlio, int & numNodi)
/* inserimento di un nuovo nodo nell’albero, indicando, come parametri dell’operazione,
la stringa che identifica il padre e la stringa che rappresenta il nuovo figlio. Se il padre non
appartiene all’albero, oppure se esiste già un altro nodo con la stessa stringa del nuovo figlio,
la funzione deve restituire false e il nuovo nodo non deve essere aggiunto all’albero. */
// questa f. si occupa anche di aggiornare opportunamente la var. "numNodi"
// nota: assumo che l'ordine dei figli non abbia importanza, quindi faccio degli inserimenti in testa (si risparmia)
{
	#ifdef DEBUG
	cerr << "affiliazione in\n";
	#endif
	// caso albero vuoto
	if (isEmpty())
	{
		tree=new Nodo;
		Nodo* aux=new Nodo;
		tree->info=padre;
		tree->primoFiglio=aux;
		tree->fratelloDx=NULL;
		tree->padre = NULL; // la radice non ha padre
		tree->depth = 0;
		aux->info=figlio;
		aux->primoFiglio=NULL;
		aux->fratelloDx=NULL;
		aux->padre = tree;
		tree->depth = 1;
		numNodi += 2;
		#ifdef DEBUG
		cerr << "affiliazione out (true, albero vuoto)\n";
		#endif
		return true;
	}
	// caso albero non vuoto
	// viene controllato che ci sia un nodo con la stringa "padre", in modo da poter aggiungere il 
	// nodo con la stringa "figlio"
	Nodo* padrePoint=checkPadre(padre);
	if (padrePoint==NULL) 
	{
		#ifdef DEBUG
		cerr << "affiliazione out (false)\n";
		#endif
		return false;
	}		
	// viene controllato che non ci sia già un nodo con la stringa "figlio" 
	if (!checkFiglio(figlio))
	{	
		#ifdef DEBUG
		cerr << "affiliazione out (false)\n";
		#endif
		return false;
	}
	// viene inserito il nodo con la stringa "figlio"
	// codice per inserire in coda (da aggiungere l'inizializzazione del campo padre e del campo
	// depth e l'incremento della var. numNodi)
	/*Nodo* aux=new Nodo;
	aux->info=figlio;
	aux->primoFiglio=NULL;
	aux->fratelloDx=NULL;
	if (padrePoint->primoFiglio == NULL) padrePoint->primoFiglio = aux;
	else
	{
		Nodo * cur = padrePoint->primoFiglio;
		while (cur->fratelloDx != NULL) cur = cur->fratelloDx;
		cur->fratelloDx=aux;
	}*/
	// codice per inserire in testa
	Nodo* aux=new Nodo;
	aux->info=figlio;
	aux->primoFiglio=NULL;
	aux->fratelloDx=padrePoint->primoFiglio;
	aux->padre = padrePoint;
	aux->depth = padrePoint->depth + 1;
	padrePoint->primoFiglio=aux; // nota: NON padrePoint=aux
	numNodi++;
	#ifdef DEBUG
	cerr << "affiliazione out (true)\n";
	#endif
	return true;
}

Nodo* Albero::checkPadre(const string & padre) 
// restituisce un puntatore a NULL se non è presente un nodo contenente la stringa "padre", 
// altrimenti restituisce un puntatore al nodo contenente la stringa "padre" (struttura simile a 
// quella della f. bfs)
{
	#ifdef DEBUG
	cerr << "checkPadre in\n";
	#endif
	Nodo* padrePoint=NULL;
	if (isEmpty())
	{	
		#ifdef DEBUG
		cerr << "checkPadre out (padrePoint==NULL, albero vuoto)\n";
		#endif
		return padrePoint;
	}
	Queue que;
	Nodo* aux=tree;
	que.enqueue(aux);
	while (!que.isEmpty())
	{
		aux=que.first();
		if (aux->info==padre)
		{
			#ifdef DEBUG
			cerr << "checkPadre out (padrePoint!=NULL)\n";
			#endif
			return padrePoint=aux;
		}
		aux=aux->primoFiglio;
		que.dequeue();		
		while (aux!=NULL)
		{
			que.enqueue(aux);
			aux=aux->fratelloDx;
		}	
	}
	#ifdef DEBUG
	cerr << "checkPadre out (padrePoint==NULL)\n";
	#endif
	return padrePoint;
}

bool Albero::checkFiglio(const string & figlio) 
// restituisce true se il figlio non è nell'albero, false altrimenti (struttura simile alla f. bfs)
{
	#ifdef DEBUG
	cerr << "checkFiglio in\n";
	#endif	
	if (isEmpty()) 
	{	
		#ifdef DEBUG
		cerr << "checkFiglio out (true)\n";
		#endif	
		return true;
	}	
	Queue que;
	Nodo* aux=tree;
	que.enqueue(aux);
	while (!que.isEmpty())
	{
		aux=que.first();
		if (aux->info==figlio) 
		{
			#ifdef DEBUG
			cerr << "checkFiglio out (false)\n";
			#endif			
			return false;
		}
		aux=aux->primoFiglio;
		que.dequeue();		
		while (aux!=NULL)
		{
			que.enqueue(aux);
			aux=aux->fratelloDx;
		}	
	}
	#ifdef DEBUG
	cerr << "checkFiglio out (true)\n";
	#endif	
	return true;
}

string Albero::bfs()
// adattata rispetto a quella dell'es. 3 per produrre la visualizzazione strutturata
// nella coda vengono inseriti i puntatori ai nodi e non i nodi (si risparmia)
{
	#ifdef DEBUG
	cerr << "bfs in\n";
	#endif		
	if (isEmpty())
	{	
		#ifdef DEBUG
		cerr << "bfs out\n";
		#endif			
		return "Albero vuoto\n";
	}	
	Queue que;
	string str;
	int gradoAux;
	Nodo* aux=tree;
	que.enqueue(aux);
	while (!que.isEmpty())
	{
		aux=que.first();
		if ((gradoAux = grado(aux)) != 0) str+=aux->info + " "; // il nomde del nodo qui inserito
		// nella stringa sarà il primo di una data riga, se il grado del nodo appena estratto dalla
		// coda è == 0, il nome del nodo, se fosse messo nella stringa, occuperebbe da solo una riga
		// e ciò non sarebbe consistente col formato dell'output voluto (uguale a quello del'input)
		aux=aux->primoFiglio;
		que.dequeue();
		while (aux!=NULL)
		{
			que.enqueue(aux);
			str += aux->info + " "; // vengono inseriti nella stringa i figli del nodo inserito 
			// nella stringa prima del while, sulla stessa riga di quest'ultimo. Notare che i figli
			// vengono inseriti nella stringa, ma anche nella coda, e quando verranno estratti da
			// questa, fuori dal while, verranno reinseriti nella stringa come primi elementi di una
			// data riga
			aux=aux->fratelloDx;
		}
		if (gradoAux != 0) str += "\n"; // se il grado dell'ultimo nodo estratto dalla coda era == 0
		// il nome del nodo non è stato inserito nella stringa e quindi non c'è bisogno di andare a
		// capo
	}
	#ifdef DEBUG
	cerr << "bfs out\n";
	#endif
	return str;
}

int Albero::grado(Nodo * n)
// restituisce il grado del nodo passato come parametro
{
	Nodo * aux = n->primoFiglio;
	int i = 0; // la dichiarazione di "i" va fatta prima del for, altrimenti "i" vive solo nello
			   // scope del for medesimo
	for (i = 0; aux != NULL; i++) aux = aux->fratelloDx;
	return i;
}

bool Albero::erase(const string & nomeNodo, int & numNodi)
// cancella, se possibile, il nodo di nome "nomeNodo" e decrementa di 1 la var. "numNodi"
{
	// se l'albero è vuoto, non esiste il nodo da cancellare
	if (isEmpty()) return false; 
	// se il nodo da cancellare è la radice e questa ha figli, la cancellazione non si fa
	if (tree->info == nomeNodo && tree->primoFiglio != NULL) return false;	
	// se il nodo non fa parte dell'albero, la cancellazione non si può fare
	Nodo * nodo = checkPadre(nomeNodo); // salvo il valore di ritorno: se non è == NULL, serve più 
										// avanti nel codice
	if (nodo == NULL) return false;
 	// cancellazione nodo:
	// se il nodo da cancellare ha il "primoFiglio", questo è collegato dopo l'ultimo dei fratelli
	// del nodo da cancellare e poi a lui e a tutti i fratelli alla sua dx è cambiato opportunamente
	// il campo padre e il campo depth
	if (nodo->primoFiglio != NULL) 
	{
		cerr << "1\n";
		Nodo * cur = nodo;
		while (cur->fratelloDx != NULL)
		{	
			cerr << "1\n";
			cur = cur->fratelloDx;
		}
		cur->fratelloDx = nodo->primoFiglio;
		while (cur->fratelloDx != NULL)
		{
			cur->fratelloDx->padre = nodo->padre;
			cur->fratelloDx->depth = nodo->depth;
			cur = cur->fratelloDx;
		}
	}
	// se il nodo da cancellare è il "primoFiglio" di suo padre, si connette il padre al fratelloDx
	// del nodo da cancellare
	if (nodo->padre->primoFiglio->info == nodo->info) nodo->padre->primoFiglio = nodo->fratelloDx;
	// altrimenti si scorrono i fratelli del nodo da cancellare fino a quello di sx del nodo da 
	// cancellare e poi si connette il fratello di sx del nodo da cancellare al fratelloDx del nodo
	// da cancellare
	else 
	{
		Nodo * cur = nodo->padre->primoFiglio;
		// nota: il caso in cui il nodo da cancellare sia il "primoFiglio" di suo padre ricade nel 
		// ramo if, quindi, se si arriva a questo punto, almeno un fratello a sx del nodo da
		// cancellare c'è sicuramente e quindi si può scrivere "cur->fratelloDx->info", anche se il
		// nodo da cancellare non ha fratelloDx
		while (cur->fratelloDx->info != nodo->info) cur = cur->fratelloDx;
		cur->fratelloDx = nodo->fratelloDx;
	}
	delete nodo;
	numNodi--;
	return true;
}

bool Albero::minCommonAncestor(const string & nodoA, const string & nodoB, string & ancestor)
// se il minimo antenato comune è presente, restituisce true e il minimo antenato comune (parametro
// OUT ancestor) dei due nodi di nome nodoA e nodoB. Altrimenti restituisce false
{
	// vengono prima gestiti i casi in cui il minimo antenato comune non è presente
	// se nodoA o nodoB sono la radice, è restituito false
	if (nodoA == tree->info || nodoB == tree->info) return false; 
	// se uno od entrambi i nodi non sono presenti nell'albero, è restituito false
	// notare che vengono salvati i puntatori ai due nodi, perchè, se non sono uguali a NULL,
	// serviranno più avanti
	Nodo * nodoAPt = checkPadre(nodoA);
	Nodo * nodoBPt = checkPadre(nodoB);
	if (nodoAPt == NULL || nodoBPt == NULL) return false;
	// se si è arrivatoi a questo punto, il minimo antenato comune è presente
	// se i due nomi passati come parametri sono uguali, è restituito il nome del padre del nodo di
	// nome nodoA == nodoB
	if (nodoA == nodoB)
	{
		ancestor = nodoAPt->padre->info;
		return true;
	}
	if (nodoAPt->depth > nodoBPt->depth) // se la profondità di nodoA è maggiore dellla profondità  
									 	 // di nodoB
	{
		while (nodoAPt->depth != nodoBPt->depth) nodoAPt = nodoAPt->padre; //a partire da nodoA si
		// sale di padre in padre finchè non si raggiunge la profondità di nodoB
		if (nodoAPt->info == nodoBPt->info) ancestor = nodoAPt->padre->info; // se si è arrivati al
		// nodoB, si restituisce il padre di quest'ultimo
		else // altrimenti si sale di padre in padre sia da nodoB, sia dal nodo a cui si è giunti
		// risalendo a partire da nodoA, finchè non si arriva allo stesso nodo e quest'ultimo sarà
		// il minimo antenato comune
		{
			while (nodoAPt->info != nodoBPt->info)
			{
				nodoAPt = nodoAPt->padre;
				nodoBPt = nodoBPt->padre; 
			}
			ancestor = nodoAPt->info;
		}
		return true;
	}
	else // se la profondità di nodoB è maggiore dellla profondità di nodoA
	{
		while (nodoBPt->depth != nodoAPt->depth) nodoBPt = nodoBPt->padre; // a partire da nodoB si
		// sale di padre in padre finchè non si raggiunge la profondità di nodoA
		if (nodoAPt->info == nodoBPt->info) ancestor = nodoAPt->padre->info; // se si è arrivati al
		// nodoA, si restituisce il padre di quest'ultimo
		else // altrimenti si sale di padre in padre sia da nodoA, sia dal nodo a cui si è giunti
		// risalendo a partire da nodoB, finchè non si arriva allo stesso nodo e quest'ultimo sarà
		// il minimo antenato comune
		{
			while (nodoBPt->info != nodoAPt->info)
			{
				nodoBPt = nodoBPt->padre;
				nodoAPt = nodoAPt->padre; 
			}
			ancestor = nodoBPt->info;
		}
		return true;
	}
}
