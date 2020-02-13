#include "heap.h"
#include <iostream> // per l'input da tastiera e l'output a schermo

Veicolo riempiVeic(istringstream & iStSt)
// inizializza tutti i campi di una var. di tipo Veicolo con le info. contenute nello stream passato
// come parametro
{
	Veicolo v; // i campi di Veicolo sono: targa, velMed, tr
	string targa;
	float velMed;
	Tragitto tr; // l'istanza di Tragitto è un vector di elem. di tipo Tappa
	Tappa t; // i campi di Tappa sono: citta, distPrev
	string citta;
	float distPrev;
	iStSt >> targa >> citta;
	v.targa = targa;
	t.citta = citta;
	t.distPrev = 0; // la distanza dalla città attraversata precedentemente è 0 nella prima var. di
					// tipo Tappa, perchè t.città inizialmente contiene la città di partenza 
	tr.enqueue(t); // la Tappa i cui campi sono appena stati inizializzati è inserita nel Tragitto
				   // (che è una coda)
	while (true)
	{
		iStSt >> distPrev >> citta;
		if (iStSt.eof()) // se citta contiene lo "eof", allora "distPrev" contiene la velocità media
						 // del veicolo e non ci sono più tappe da aggiungere al tragitto (vd. 
						 // formato input)
		{
			v.velMed = distPrev;
			v.tr = tr;
			return v;
		}
		else // altrimenti si aggiunge un'altra tappa al tragitto
		{
			t.citta = citta;
			t.distPrev = distPrev;
			tr.enqueue(t);
		}
	}
}

int main()
{
	Veicolo listaVeic[length]; // per length vd. "heap.h" 
	unsigned int numVeic;
	while (true)
	{
		cout << "Di quanti veicoli vuoi simulare il movimento?\n";
		cin >> numVeic;
		if (numVeic > 20) cout << "Si può simulare il movimento di massimo 20 veicoli\n";
		else break;
	}
	cin.ignore(100, '\n'); // vengono eliminati dal flusso caratteri finchè non ne sono
						   // stati eliminati 100 o finchè non si incontra il carattere
				           // '\n' (nota: si potrebbe avere una soluzione migliore 
						   // usando i template nella chiamata alla ignore).
						   // Quest'operazione va fatta o la riga "getline(cin, line);" inserisce
						   // in "line" il num. di veicoli appena digitato da tastiera
	string line;
	cout << "Inserisci le informazioni per ogni veicolo nel formato prestabilito\n";
	for (int i = 0; i < numVeic; i++)
	{
		getline(cin, line);
		istringstream iStSt(line);
		listaVeic[i] = riempiVeic(iStSt);
	}
	cout << endl;
	Heap h;
	for (int i = 0; i < numVeic; i++) // con questo for, vengono creati e inseriti nello heap i 
									  // primi numVeic eventi (essendo i primi, il loro timestamp è
									  // 0)
	{
		Evento e;
		e.timestamp = 0;
		e.v = listaVeic[i];
		h.insert(e);
	}
	while (!h.isEmpty()) // cosa deve fare questo ciclo è descritto nelle specifiche
	{
		Evento e;
		h.findMin(e); // non è necessario intercettare il valore di ritorno dell f. findMin, perchè
					  // se lo heap fosse vuoto, non si entrerebbe nello while
		h.deleteMin();
		cout << e.printStr(e) << endl;
		e.v.tr.dequeue(); // le tappa del tragitto di un veicolo di un certo evento è eliminata e lo
						  // stesso evento sarà reinserito nello heap avendo come prima tappa quella 
						  // successiva a quella appena eliminata
		if (!e.v.tr.isEmpty()) // se il tragitto del veicolo dell'evento non è vuoto
		{
			// è aggiornato il timestamp ("* 3600" perchè si vuole il tempo in s in output, ma 
			// l'input è in k / h)
			e.timestamp += ((e.v.tr.first()).distPrev / e.v.velMed) * 3600;
			// ad "e" sono stati aggiornati tragitto e timestamp, quindi può essere reinserito nello
			// heap
			h.insert(e);
		}
	}
	return 0;
}
