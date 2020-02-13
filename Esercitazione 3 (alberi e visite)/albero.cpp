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

bool Albero::affiliazione(const string & padre, const string & figlio)
/* inserimento di un nuovo nodo nell’albero, indicando, come parametri dell’operazione,
la stringa che identifica il padre e la stringa che rappresenta il nuovo figlio. Se il padre non
appartiene all’albero, oppure se esiste già un altro nodo con la stessa stringa del nuovo figlio,
la funzione deve restituire false e il nuovo nodo non deve essere aggiunto all’albero. */
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
		aux->info=figlio;
		aux->primoFiglio=NULL;
		aux->fratelloDx=NULL;
		#ifdef DEBUG
		cerr << "affiliazione out (true, albero vuoto)\n";
		#endif
		return true;
	}
	// caso albero non vuoto
	// viene controllato che ci sia un nodo con la stringa "padre", in modo da poter aggiungere il nodo con la stringa "figlio"
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
	Nodo* aux=new Nodo;
	aux->info=figlio;
	aux->primoFiglio=NULL;
	aux->fratelloDx=padrePoint->primoFiglio;
	padrePoint->primoFiglio=aux; // nota: NON padrePoint=aux;
	#ifdef DEBUG
	cerr << "affiliazione out (true)\n";
	#endif
	return true;
}

Nodo* Albero::checkPadre(const string & padre) 
// restituisce un puntatore a NULL se non è presente un nodo contenente la stringa "padre", altrimenti restituisce un puntatore al nodo contenente la stringa "padre" (struttura simile a quella della f. bfs)
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
	Nodo* aux=tree;
	que.enqueue(aux);
	while (!que.isEmpty())
	{
		aux=que.first();	
		str+=aux->info+"\n";
		aux=aux->primoFiglio;
		que.dequeue();		
		while (aux!=NULL)
		{
			que.enqueue(aux);
			aux=aux->fratelloDx;
		}	
	}
	#ifdef DEBUG
	cerr << "bfs out\n";
	#endif
	return str;
}
