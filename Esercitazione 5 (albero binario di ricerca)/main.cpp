#include "BST.h"
#include <fstream>

int main()
{
	BST myBST;
	Impiegato imp;
	string nome, cognome, s;
	int annoAssunzione;
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
		ist >> cognome;
		if (cognome == "0") break;
		ist >> nome;
		if (nome == "0") break;
		ist >> annoAssunzione;
		if (annoAssunzione == 0) break;
		imp.writeCognome(nome);
		imp.writeNome(cognome);
		imp.writeAnnoAssunzione(annoAssunzione);
		myBST.insert(imp);
	}		
	// input da tastiera
	/*cout << "procedi a inserire (0 per terminare)\n";
	for(;;) 
	{
		cout << "Cognome: ";
		cin >> cognome;
		if (cognome == "0") break;		
		cout << "Nome: ";		
		cin >> nome;
		if (nome == "0") break;
		// se ora usassi un codice analogo al precedente per l'inserimento dell'anno di assunzione,
		// nel caso l'utente inserisse caratteri alfabetici invece che numerici, si entrerebbe in un
		// ciclo infinito. Questo problema è gestito nel seguente "while (true)"	
		while (true)
		{	
			cout << "Anno assunzione: ";
			if (cin >> annoAssunzione) // se il flusso non va in stato di errore (è stato inserito
									   // un numero)
				break;
			else // se "cin" è andato in stato d'errore (non è stato inserito un numero)
			{
				cout << "Devi inserire un numero!\n";				
				cin.clear(); // viene riportato "cin" in stato normale 
				cin.ignore(100, '\n'); // vengono eliminati dal flusso caratteri finchè non ne sono
									   // stati eliminati 100 o finchè non si incontra il carattere
									   // '\n' (nota: si potrebbe avere una soluzione migliore 
									   // usando i template nella chiamata alla ignore)
			}
		}
		if (annoAssunzione == 0) break;
		imp.writeCognome(nome);
		imp.writeNome(cognome);
		imp.writeAnnoAssunzione(annoAssunzione);
		myBST.insert(imp);
	}*/
	while (true)
	{
		cout << endl 
			 << "a) Visualizza l'elenco ordinato degli impiegati inseriti\n"
				"b) Cerca un'impiegato\n"
				"c) Cancella un impiegato\n"
				"d) Esci\n\n"
				"Fai la tua scelta: ";
		cin >> s;
		cout << endl;
		if (s.size() > 1) s = "z"; // se è stato inserito più di un carattere, si andrà 
								   // direttamente all'ultimo "else" della prossima cascata di 
								   // "else if"
		if (s == "a")
		{
			cout << "Ecco l'elenco ordinato degli impiegati inseriti:\n\n";
			cout << myBST.DFSSimmetrica();
		}
		else if (s == "b")
		{
			cout << "Inserisci i dati identificativi dell'impiegato da cercare\n\n";
			cout << "Cognome: ";
			cin >> cognome;
			cout << "Nome: ";
			cin >> nome;
			cout << "Anno assunzione: ";
			cin >> annoAssunzione;
			imp.writeCognome(nome);
			imp.writeNome(cognome);
			imp.writeAnnoAssunzione(annoAssunzione);
			cout << endl;
			if (myBST.search(imp) == NULL)
				cout << "L'impiegato non è presente\n";
			else 
				cout << "L'impiegato è presente\n";
		}
		else if (s == "c")
		{
			cout << "Inserisci i dati identificativi dell'impiegato da cancellare\n\n";
			cout << "Cognome: ";
			cin >> cognome;
			cout << "Nome: ";
			cin >> nome;
			cout << "Anno assunzione: ";
			cin >> annoAssunzione;
			imp.writeCognome(nome);
			imp.writeNome(cognome);
			imp.writeAnnoAssunzione(annoAssunzione);
			cout << endl;
			if (myBST.erase(imp)) 
				cout << "L'impiegato è stato cancellato\n";
			else
				cout << "L'impiegato non è presente, quindi non può essere cancellato\n";
		}
		else if (s == "d") 
		{
			cout << "Bye, bye!\n";
			break;
		}
		else
			cout << "Devi inserire una sola lettera e questa dev'essere compresa fra quelle del menù\n";
	}
}
