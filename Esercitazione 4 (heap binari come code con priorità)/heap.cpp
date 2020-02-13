#include "heap.h"

Heap::Heap()
{
	n = 0;
}

bool Heap::isEmpty()
{
	return (n == 0);
}

bool Heap::findMin(Evento & e)
{
	if (isEmpty()) return false;
	e = hArray[0];
	return true;
}

int Heap::minTimestamp(int i, int j)
// prende in input gli indici di due elem. dell'array che rappresenta lo heap e restituisce l'indice 
// dell'elemento di chiave minore tra i due. Se le chiavi dei due elem. sono uguali, viene 
// restituito l'indice "i". In questa f. non si controlla che i due indici corrispondano a posizioni
// dell'array effettivamente occupate, nè che non siano < 0, nè che non siano più grandi del numero 
// di caselle dell'array
{
	if (hArray[i].timestamp > hArray[j].timestamp) return i;
	else if (hArray[j].timestamp > hArray[i].timestamp) return j;
	else return i;
}

void Heap::muoviBasso(int i)
{
	// finchè i non è la posizione di una foglia
	while (2 * i + 2 <= n - 1 && 2 * i + 1 <= n - 1)
	{
		if (2 * i + 2 <= n - 1) // se hArray[i] ha il figlio di dx (e quindi anche quello di sx, essendo
							    // lo heap binario un albero binario completo)
		{
			// se la chiave di hArray[i] < chiave maggiore tra quelle dei suoi figli, si scambia 
			// hArray[i] col figlio di chiave maggiore. Se invece hArray[i] >= chiave maggiore tra
			// quelle dei suoi figli, hArray[i] è in posizione corretta, quindi si esce dal ciclo e
			// dalla funzione
			int j = minTimestamp(i * 2 + 1, i * 2 + 2);
			if (hArray[i].timestamp < hArray[j].timestamp)
			{
				Evento aux;
				aux = hArray[i];
				hArray[i] = hArray[j];
				hArray[j] = aux;
				i = j; // viene aggiornata la posizione dell'elem. da muovere verso il basso
			}
			else break;
		}
		else // se hArray[i] non ha il figlio dx (ha sicuramente quello sx, essendo lo heap binario 
			 // un albero binario completo e non potendo essere una foglia, altrimenti non si 
			 // sarebbe entrati nel corpo dello while)
		{	
			// se la chiave di hArray[i] < chiave del suo figlio sx, si scambia hArray[i] col suo 
			// figlio sx. Se invece hArray[i] >= chiave del suo figlio sx, hArray[i] è in posizione
			// corretta, quindi si esce dal ciclo e dalla f.
			if (hArray[i].timestamp < hArray[2 * i + 1].timestamp) 
			{
				Evento aux;
				aux = hArray[i];
				hArray[i] = hArray[2 * i + 1];
				hArray[2 * i + 1] = aux;
				i = 2 * i + 1; // viene aggiornata la pos. dell'elem da muovere verso il basso
			}
			else break;
		}
	}
}

bool Heap::deleteMin()
{
	if (isEmpty()) return false;
	Evento aux;
	aux = hArray[0];
	hArray[0] = hArray[n - 1];
	hArray[n - 1] = aux;
	muoviBasso(0);
	n--; // va decrementata dopo aver chiamato la muoviBasso
	return true;
}

void Heap::muoviAlto(int i)
{
	// finchè i non è la posizione della radice	e la chiave di hArray[i] > di quella di suo padre,
	// vengono scambiati di posto hArray[i] e suo padre
	Evento aux;
	while (i != 0 && hArray[i].timestamp < hArray[(i - 1) / 2].timestamp) 
	{
		aux = hArray[(i - 1) / 2];
		hArray[(i - 1) / 2] = hArray[i];
		hArray[i] = aux;
		i = i - 1 / 2; // si aggiorna la pos. dell'elem. da spostare verso l'alto
	}
}

void Heap::insert(Evento e)
{
	n++;
	hArray[n-1] = e;
	muoviAlto(n-1);
}
