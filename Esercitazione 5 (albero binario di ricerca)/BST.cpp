#include "BST.h"

BST::BST()
{
	#ifdef DEBUG
	cerr << "BST in\n";
	#endif
	tree = NULL;
	#ifdef DEBUG
	cerr << "BST out\n";
	#endif
}

string BST::DFSSimmetrica()
{
	#ifdef DEBUG
	cerr << "DFSSimmetrica in\n";
	#endif
	if (tree == NULL) /* se avessi messo questo controllo nella f. DFSSimmetricaAux, non sarebbe
					  stato eseguito una volta sola, ma ad ogni chiamata ricorsiva */
		return "L'albero è vuoto\n";
	string str;
	/* nota: se avessi dichiarato la var. str nella DFSSimmetricaAux, la dichiarazione sarebbe
	avvenuta ad ogni chiamata ricorsiva e, a parte questo, il codice della DFSSimmetricaAux si
	sarebbe complicato, quindi ho optato per dichiarare la var. str qui e passarla come parametro
	per riferimento	*/
	DFSSimmetricaAux(tree, str);
	return str;
	#ifdef DEBUG
	cerr << "DFSSimmetrica out\n";
	#endif
}

void BST::DFSSimmetricaAux(NodoBST* nodoCorrentePtr, string & str)
{
	#ifdef DEBUG
	cerr << "DFSSimmetricaAux in\n";
	#endif
	if (nodoCorrentePtr == NULL) return;
	DFSSimmetricaAux(nodoCorrentePtr->figlioSx, str);
	str = str + nodoCorrentePtr->imp.printImp() + "\n";
	DFSSimmetricaAux(nodoCorrentePtr->figlioDx, str);
	#ifdef DEBUG
	cerr << "DFSSimmetricaAux out\n";
	#endif
}

bool BST::insert(const Impiegato & imp)
{
	#ifdef DEBUG
	cerr << "insert in\n";
	#endif
	if (tree == NULL) // caso albero vuoto
	{
		tree = new NodoBST;
		tree->padre = NULL; // la radice non ha padre
		tree->figlioSx = NULL;
		tree->figlioDx = NULL;
		tree->imp = imp;
		#ifdef DEBUG
		cerr << "insert out (true, inserimento in radice)\n";
		#endif
		return true;
	}
	NodoBST* padre = searchPadre(imp); // la searchPadre restituisce NULL se il nodo da aggiungere �
									   // gi� presente, altrimenti restituisce il puntatore al nodo
									   // a cui va aggiunto il nodo da aggiungere
	if (padre != NULL) // se il nodo contenente imp non è già presente
	{
		if (padre->imp.orderImp(imp) == maggiore)
		// se l'imp che si vuole inserire è > imp del nodo padre, il nuovo nodo verrà inserito
		// come figlio dx
		{
			NodoBST* aux = new NodoBST;
			aux->imp = imp;
			aux->padre = padre;
			aux->figlioDx = NULL;
			aux->figlioSx = NULL;
			padre->figlioDx = aux;
			#ifdef DEBUG
			cerr << "insert out (true, inserimento come figlio dx di " << padre->imp.readCognome() << ")\n";
			#endif
			return true;
		}
		// altrimenti verrà inserito come figlio sx
		{
			NodoBST* aux = new NodoBST;
			aux->imp = imp;
			aux->padre = padre;
			aux->figlioDx = NULL;
			aux->figlioSx = NULL;
			padre->figlioSx = aux;
			#ifdef DEBUG
			cerr << "insert out (true, inserimento come figlio sx di " << padre->imp.readCognome() << ")\n";
			#endif
			return true;
		}
	return false; // si arriva a questo punto se la searchPadre ha restituito NULL (imp è già
				  // presente)
	}
}

// implementazione ricorsiva della insert

/* bool BST::insert(const Impiegato & imp)
{
	#ifdef DEBUG
	cerr << "insert in\n";
	#endif
	if (tree == NULL) // caso albero vuoto
	{
		tree = new NodoBST;
		tree->figlioSx = NULL;
		tree->figlioDx = NULL;
		tree->padre = NULL; // la radice non ha padre
		tree->imp = imp;
		#ifdef DEBUG
		cerr << "insert out (inserimento in radice)\n";
		#endif
		return true;
	}
	return insertAux(imp, tree);
	#ifdef DEBUG
	cerr << "insert out\n";
	#endif
}

bool BST::insertAux(Impiegato imp, NodoBST* & nodoCorrentePtr)
{
	#ifdef DEBUG
	cerr << "insertAux in\n";
	#endif
	// se l'imp. passato alla insertAux è = quello del nodo corrente
	if (nodoCorrentePtr->imp.orderImp(imp) == uguale)
	{
		#ifdef DEBUG
		cerr << "insertAux out (imp nodo corrente == imp nodo passato)\n";
		#endif
		return false;
	}
	// se l'imp passato alla insertAux è < quello del nodo corrente
	if (nodoCorrentePtr->imp.orderImp(imp) == minore)
	{
		// se il nodo corrente ha figlio sx è fatta una chiamata ricorsiva sul figlio sx
		if (nodoCorrentePtr->figlioSx != NULL) return insertAux(imp, nodoCorrentePtr->figlioSx);
		// altrimenti è inserito l'imp passato alla insertAux come figlio sx
		else // nota: la keyword "else" non può essere omessa, altrimenti, terminata la chiamata
			 // ricorsiva, viene in ogni caso appeso il nuovo figlio, tagliando di fatto il
		 	 // sottoalbero già esistente
		{
			NodoBST* aux = new NodoBST;
			nodoCorrentePtr->figlioSx = aux;
			aux->imp = imp;
			aux->figlioSx = aux->figlioDx = NULL;
			aux->padre = nodoCorrentePtr;
			#ifdef DEBUG
			cerr << "insertAux out (imp nodo passato < imp nodo corrente)\n";
			#endif
			return true;
		}
	}
	// a questo punto l'unico caso rimasto è quello in cui l'imp passato alla insertAux > quello
	// del nodo corrente
	// se il nodo corrente ha figlio dx è fatta una chiamata ricorsiva sul figlio dx
	if (nodoCorrentePtr->figlioDx != NULL) return insertAux(imp, nodoCorrentePtr->figlioDx);
	// altrimenti è inserito l'imp passato alla insertAux come figlio dx
	else // nota: la keyword "else" non può essere omessa, altrimenti, terminata la chiamata
		 // ricorsiva, viene in ogni caso appeso il nuovo figlio, tagliando di fatto il sottoalbero
		 // già esistente
	{
		NodoBST* aux = new NodoBST;
		nodoCorrentePtr->figlioDx = aux;
		aux->imp = imp;
		aux->figlioSx = aux->figlioDx = NULL;
		aux->padre = nodoCorrentePtr;
		#ifdef DEBUG
		cerr << "insertAux out (imp nodo passato > imp nodo corrente)\n";
		#endif
		return true;
	}
} */

NodoBST* BST::search(const Impiegato & imp)
{
	if (tree == NULL) return NULL; // caso albero vuoto
	NodoBST* nodoCorrentePtr = tree;
	while (nodoCorrentePtr != NULL)
	{
		if (nodoCorrentePtr->imp.orderImp(imp) == uguale)
			return nodoCorrentePtr;
		if (nodoCorrentePtr->imp.orderImp(imp) == minore)
			nodoCorrentePtr = nodoCorrentePtr->figlioSx;
		else
			nodoCorrentePtr = nodoCorrentePtr->figlioDx;
	}
	return NULL;
}

NodoBST* BST::searchPadre(const Impiegato & imp)
// la searchPadre restituisce NULL se l'imp. passatole � gi� presente, altrimenti restituisce il
// puntatore al nodo a cui andrebbe aggiunto il nodo contenente l'imp. passatole
// nota: questa f. � chiamata solo dalla insert e il caso "albero vuoto" � gi� gestito dall'insert
// stessa, quindi nn lo gestisco anche qui
{
	#ifdef DEBUG
	cerr << "searchPadre in\n";
	#endif
	NodoBST* nodoCorrentePtr = tree;
	while (true)
	{
		// se l'impiegato è già presente è restituito NULL
		if (nodoCorrentePtr->imp.orderImp(imp) == uguale)
		{
			#ifdef DEBUG
			cerr << "searchPadre out (NULL, imp c'è già)\n";
			#endif
			return NULL;
		}
		// altrimenti è restituito il puntatore al nodo a cui andrebbe aggiunto il nodo contenente
		// imp
		if (nodoCorrentePtr->imp.orderImp(imp) == minore)
		{
			if (nodoCorrentePtr->figlioSx == NULL)
			{
				#ifdef DEBUG
				cerr << "searchPadre out (nodoCorrentePtr, imp va inserito come figlio sx di " << nodoCorrentePtr->imp.readCognome() << ")" << endl;
				#endif
				return nodoCorrentePtr;
			}
			nodoCorrentePtr = nodoCorrentePtr->figlioSx;
		}
		else
		{
			if (nodoCorrentePtr->figlioDx == NULL)
			{
				#ifdef DEBUG
				cerr << "searchPadre out (nodoCorrentePtr, imp va inserito come figlio dx di " << nodoCorrentePtr->imp.readCognome() << ")" << endl;
				#endif
				return nodoCorrentePtr;
			}
			nodoCorrentePtr = nodoCorrentePtr->figlioDx;
		}
	}
}

bool BST::erase(Impiegato imp)
// Nota: per la cancellazione e' necessario agire anche sul padre del nodo da cancellare, e dunque
// sorge il problema di come raggiungere tale nodo padre. La soluzione piu' semplice consiste
// nell'aggiungere un campo (nello "struct nodo") che punta al padre (null nel caso del nodo
// radice). In realta' e' anche possibile fare a meno di tale puntatore aggiuntivo, portandosi
// dietro il puntatore al padre man mano che si scende nell'albero alla ricerca del nodo da
// cancellare. Entrambe le soluzioni hanno il vantaggio che l'accesso al padre si ottiene in O(1)
// (tempo costante). La seconda soluzione ha il pregio di risparmiare un pochino di memoria.
{
	#ifdef DEBUG
	cerr << "erase in\n";
	#endif
	NodoBST* searchPtr = search(imp);
	// caso "imp non presente"
	if (searchPtr == NULL)
		return false;
	// caso "nodo da cancellare ha entrambi i figli"
	// nota: questo dev'essere il primo caso gestito perch� per questo caso serve anche il codice
	// scritto per gli altri casi (leggi pi� avanti per capire meglio)
	if ((searchPtr->figlioSx != NULL) && (searchPtr->figlioDx != NULL))
	{
		NodoBST* maxPtr = searchMax(searchPtr->figlioSx);
		// alla searchMax va passata la radice del sottoalbero sx del nodo restituito dalla search.
		// La f. searchMax restituisce il predecessore se le viene passato un nodo con almeno il
		// figlioSx (vd. appunti)
		searchPtr->imp = maxPtr->imp;
		searchPtr=maxPtr;
		// il predecessore, per essere tale, o � una foglia o ha solo il figlio sx, se infatti
		// avesse solo figlio dx o entrambi i figli non sarebbe il max del sottoalbero in cui si
		// trova. Quindi usciti da questo if si � o nel caso "nodo da cancellare è foglia" o in
		// quello "nodo da cancellare ha solo figlio sx", gestiti sotto
	}
	// caso "nodo da cancellare è foglia"
	if ((searchPtr->figlioSx == NULL) && (searchPtr->figlioDx == NULL))
	{
		// se il nodo da cancellare � la radice non si pu� fare un confronto tra l'imp. del nodo da
		// cancellare e quello di suo padre, perch� l'imp. del padre non esiste
		if (searchPtr->padre == NULL) tree = NULL; // viene modificato il puntatore
												   // alla radice e poi si andr�
												   // direttamente alla prossima
												   // delete
		// altrimenti viene controllato se il nodo da cancellare è figlio dx o sx, per poi
		// modificare opportunamente il padre
		else
		{
			if (searchPtr->padre->imp.orderImp(searchPtr->imp) == minore)
				searchPtr->padre->figlioSx = NULL;
			else
				searchPtr->padre->figlioDx = NULL;
		}
		// viene cancellato il nodo
		delete searchPtr;
		#ifdef DEBUG
		cerr << "erase out (true, cancellato nodo foglia)\n";
		#endif
		return true;
	}
	// caso "nodo da cancellare ha solo figlio sx"
	if ((searchPtr->figlioSx != NULL) && (searchPtr->figlioDx == NULL))
	{
		// se il nodo da cancellare � la radice non si pu� fare un confronto tra l'imp. del nodo da
		// cancellare e quello di suo padre, perch� l'imp. del padre non esiste
		if (searchPtr->padre == NULL)
		{
			tree = searchPtr->figlioSx; // viene modificato il puntatore alla radice
			searchPtr->figlioSx->padre = NULL; // si modifica opportunamente il campo padre della
												// nuova radice e poi si andr� direttamente alla
												// prossima delete
		}
		// altrimenti viene controllato se il nodo da cancellare è figlio dx o sx, per poi
		// modificare opportunamente il padre
		else
		{
			if (searchPtr->padre->imp.orderImp(searchPtr->imp) == minore)
				searchPtr->padre->figlioSx = searchPtr->figlioSx;
			else
				searchPtr->padre->figlioDx = searchPtr->figlioSx;
			searchPtr->figlioSx->padre = searchPtr->padre;
		}
		// viene cancellato il nodo
		delete searchPtr;
		#ifdef DEBUG
		cerr << "erase out (true, cancellato nodo con solo figlio sx)\n";
		#endif
		return true;
	}
	// caso "nodo da cancellare ha solo figlio dx"
	if ((searchPtr->figlioSx == NULL) && (searchPtr->figlioDx != NULL))
	{
		// se il nodo da cancellare � la radice non si pu� fare un confronto tra l'imp. del nodo da
		// cancellare e quello di suo padre, perch� l'imp. del padre non esiste
		if (searchPtr->padre == NULL) if (searchPtr->padre == NULL)
		{
			tree = searchPtr->figlioSx; // viene modificato il puntatore alla radice
			searchPtr->figlioSx->padre = NULL; // si modifica opportunamente il campo padre della
												// nuova radice e poi si andr� direttamente alla
												// prossima delete
		}
		// altrimenti viene controllato se il nodo da cancellare è figlio dx o sx, per poi
		// modificare opportunamente il padre
		else
		{
			if (searchPtr->padre->imp.orderImp(searchPtr->imp) == minore)
				searchPtr->padre->figlioSx = searchPtr->figlioDx;
			else
				searchPtr->padre->figlioDx = searchPtr->figlioDx;
			searchPtr->figlioDx->padre = searchPtr->padre;
		}
		// viene cancellato il nodo
		delete searchPtr;
		#ifdef DEBUG
		cerr << "erase out (true, cancellato nodo con solo figlio dx)\n";
		#endif
		return true;
	}
}

NodoBST* BST::searchMax(NodoBST* nodoCorrentePtr)
{
	#ifdef DEBUG
	cerr << "searchMax in\n";
	#endif
	while (nodoCorrentePtr->figlioDx != NULL)
		nodoCorrentePtr = nodoCorrentePtr->figlioDx;
	#ifdef DEBUG
	cerr << "searchMax out\n";
	#endif
	return nodoCorrentePtr;
}
