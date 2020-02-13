#include "grafo_listaAdiacenza.h"
#include <iostream>
#include <sstream>
#include <fstream>

int main()
{
	Grafo g;
	string line, origine, destinazione;
	int distanza;
	// input da file
	ifstream ist;
	ist.open("dati");
	if (!ist)
	{ 
		cerr << "Errore nell'apertura del file\n";
		return -1;
	}
	while (!ist.eof()) // nota: in realtà si potrebbe anche usare un "while(true)", perchè l'input è 
					   // terminato dalla presenza di uno 0, non dal raggiungimento della fine del
					   // file
	{
		getline(ist, line);
		istringstream is(line);
		is >> origine;
		if (origine == "0") break;
		is >> destinazione >> distanza;
		// nota: non c'è bisogno di intercettare il valore di ritorno delle prossime funzioni 
		// chiamate e cmq le chiamate vanno fatte tutte e tre ad ogni ciclo, indipendentemente dal 
		// valore di ritorno
		g.aggiungiVerticeIsolato(origine);
		g.aggiungiVerticeIsolato(destinazione);
		g.aggiungiArco(origine, destinazione, distanza);
	}
	// input da tastiera
	/*cout << "Inserisci, nel formato corretto, le informazioni sui vertici e sugli archi\n";
	while (true)
	{
		getline(cin, line);
		istringstream is(line);
		is >> origine;
		if (origine == "0") break;
		is >> destinazione >> distanza;
		// nota: non c'è bisogno di intercettare il valore di ritorno delle prossime funzioni 
		// chiamate e cmq le chiamate vanno fatte tutte e tre ad ogni ciclo, indipendentemente dal 
		// valore di ritorno
		g.aggiungiVerticeIsolato(origine);
		g.aggiungiVerticeIsolato(destinazione);
		g.aggiungiArco(origine, destinazione, distanza);		
	}*/
	cout << g.strToPrint();
	cout << endl;
	cout << "Inserisci nodo origine: ";
	cin >> origine;
	cout << "Inserisci nodo destinazione: ";
	cin >> destinazione;
	cout << endl;
	ListaAdiacenza l; // è riciclata la struct ListaAdiacenza per il cammino aciclico (vd. apposite
					  // funz.)
	distanza = 0; // per il calcolo della distanza fra i due nodi del cammino aciclico si riutilizza
	// la var. "distanza", che però contiene l'ultimo valore "distanza" inserito in input
	// precendentemente e quindi va riinizializzata a 0
	if (!g.camminoAciclico(origine, destinazione, distanza, l)) 
		cout << "Non c'è un cammino aciclico fra i due nodi\n";
	else 
	{
		cout << "Cammino aciclico:\n";
		cout << l.strToPrint();
	}
	cout << endl; // fuori dallo "if/else" perchè bisgna andare a capo in entrambi i casi
	cout << "Distanza fra i due nodi: " << distanza << endl;
	return 0;
}
