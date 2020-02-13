#include <iostream> // per l'input/output
#include <sstream> // per la var. istst
#include <fstream> // per la var. ist e altro
#include "albero.h" // per le chiamate a f. proprie di questo modulo

using namespace std;

int main()
{
	Albero a;
	string alberoStr, padre, figlio;
	char c;
	int numNodi = 0;
	// input da file
	ifstream ist;
	ist.open("input");
	if (!ist)
	{
		cerr << "Errore nell'apertura del file\n";
		return -1;
	}
	while (!ist.eof()) // nota: in realtà si potrebbe anche usare un "while(true)", perchè l'input è
					   // terminato dalla presenza di uno 0, non dal raggiungimento della fine del
					   // file
	{
		getline(ist, alberoStr);
	// input da tastiera
	/*while (true)
	{
		getline(cin, alberoStr);*/
		if (alberoStr=="0") break; // se viene inserito 0 da tastiera si esce dal while
		istringstream istst(alberoStr);
		istst >> padre;
		while (true)
		{
			istst >> figlio; // ad ogni ciclo cambia il figlio passato alla f. affiliazione, mentre il padre rimane lo stesso
			if (!istst) break;
			if (!a.affiliazione(padre, figlio, numNodi)) break;
		}
	}
	while (true)
	{
		cout <<
		"a) ricerca del minimo antenato comune di due nodi\n"
		"b) cancellazione di un nodo\n"
		"c) visualizzazione strutturata dell'albero\n"
		"d) visualizzazione del numero dei nodi presenti nell'albero\n"
		"e) uscita\n\n"
		"Fai la tua scelta: ";
		cin >> c;
		cout << endl;
		if (c == 'a')
		{
			cout << "Inserisci i nomi dei nodi di cui cercare l'antenato comune\n\n"
					"Primo nodo: ";
			cin >> padre; // si ricicla la stringa "padre"
			cout << "Secondo nodo: ";
			cin >> figlio; // si ricicla la stringa "figlio"
			cout << endl;
			if (a.minCommonAncestor(padre, figlio, alberoStr)) // si ricicla la stringa "alberoStr"
				cout << "Il minimo antenato comune è: " << alberoStr;
			else cout << "Non c'è il minimo antenato comune fra i due nodi indicati";
			cout << endl << endl; // fuori dallo "if/else" perchè serve per entrambi
		}
		else if (c == 'b')
		{
			cout << "Inserisci il nome del nodo da cancellare: ";
			cin >> alberoStr; // è riutilizzata la var. "alberoStr"
			cout << endl;
			if (a.erase(alberoStr, numNodi)) cout << "Il nodo è stato cancellato";
			else cout << "L'albero è vuoto o il nodo non è presente nell'albero o il nodo è la "
						 "radice e questa ha figli: la cancellazione non può essere fatta";
			cout << endl << endl; // fuori dallo "if/else" perchè serve per entrambi
		}
		else if (c == 'c')
		{
			cout << a.bfs(); // la stringa restituita dalla f. bfs contiene un "a capo" finale
			cout << endl;
		}
		else if (c == 'd')
			cout << "Numero di nodi presenti nell'albero: " << numNodi << endl << endl;
		else if (c == 'e') return 0;
	}
}
