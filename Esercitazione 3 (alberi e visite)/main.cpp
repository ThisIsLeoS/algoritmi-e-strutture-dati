#include <iostream> // per l'input/output
#include <sstream> // per la var. istst
#include "albero.h" // per le chiamate a f. proprie di questo modulo

using namespace std;

int main()
{
	Albero a;	
	string alberoStr;
	while (true)
	{
		getline(cin, alberoStr);
		if (alberoStr=="0") break; // se viene inserito 0 da tastiera si esce dal while	
		istringstream istst(alberoStr);
		string padre, figlio;
		istst >> padre;
		while (true)
		{
			istst >> figlio; // ad ogni ciclo cambia il figlio passato alla f. affiliazione, mentre il padre rimane lo stesso
			if (!istst) break;
			if (!a.affiliazione(padre, figlio)) break;
		}
	}
	cout << a.bfs(); // la stringa restituita dalla f. bfs contiene già un "a capo" finale
}
