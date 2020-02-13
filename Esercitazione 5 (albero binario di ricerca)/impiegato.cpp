#include "impiegato.h"

string Impiegato::readNome()
{
	#ifdef DEBUG
	cerr << "readNome in\n";
	#endif
	return nome;
	#ifdef DEBUG
	cerr << "readNome out\n";
	#endif
}

string Impiegato::readCognome()
{
	#ifdef DEBUG
	cerr << "readCognome in\n";
	#endif
	return cognome;
	#ifdef DEBUG
	cerr << "readCognome out\n";
	#endif
}

int Impiegato::readAnnoAssunzione()
{
	#ifdef DEBUG
	cerr << "readAnnoAssunzione in\n";
	#endif
	return annoAssunzione;
	#ifdef DEBUG
	cerr << "readAnnoAssunzione out\n";
	#endif
}

void Impiegato::writeNome(const string & name)
{
	#ifdef DEBUG
	cerr << "writeNome in\n";
	#endif
	nome = name;
	#ifdef DEBUG
	cerr << "writeNome out\n";
	#endif
}

void Impiegato::writeCognome(const string & surname)
{
	#ifdef DEBUG
	cerr << "writeCognome in\n";
	#endif
	cognome = surname;
	#ifdef DEBUG
	cerr << "writeCognome out\n";
	#endif
}

void Impiegato::writeAnnoAssunzione(const int & year)
{
	#ifdef DEBUG
	cerr << "writeAnnoAssunzione in\n";
	#endif
	annoAssunzione = year;
	#ifdef DEBUG
	cerr << "writeAnnoAssunzione out\n";
	#endif
}

string Impiegato::printImp()
{
	#ifdef DEBUG
	cerr << "printImp in\n";
	#endif	
	/* con le seguenti 3 linee di codice viene scritto nel flusso stst l'anno di assunzione come 
	stringa (mentre la var. annoAssunzione è intera) */
	string strImp;
	stringstream stst;
	stst << annoAssunzione;
	return strImp = nome + ", " + cognome  + ", " + stst.str(); /* "stst.str()" restituisce la 
																stringa contenuta nel flusso stst */
	#ifdef DEBUG
	cerr << "printImp out\n";
	#endif
}

Confronto Impiegato::orderImp(const Impiegato & imp)
{
	#ifdef DEBUG
	cerr << "orderImp in\n";
	#endif
	if (imp.cognome > cognome) 
	{
		#ifdef DEBUG
		cerr << "orderImp out\n";
		#endif		
		return maggiore;
	}
	if (imp.cognome < cognome) 
	{
		#ifdef DEBUG
		cerr << "orderImp out\n";
		#endif		
		return minore;
	}
	else
	{
		if (imp.nome > nome) 
		{	
			#ifdef DEBUG
			cerr << "orderImp out\n";
			#endif		
			return maggiore;
		}
		if (imp.nome < nome) 
		{	
			#ifdef DEBUG
			cerr << "orderImp out\n";
			#endif	
			return minore;
		}
		else
		{
			if (imp.annoAssunzione > annoAssunzione) 
			{
				#ifdef DEBUG
				cerr << "orderImp out\n";
				#endif
				return maggiore;
			}
			if (imp.annoAssunzione < annoAssunzione) 
			{	
				#ifdef DEBUG
				cerr << "orderImp out\n";
				#endif	
				return minore;
			}
			else 
			{
				#ifdef DEBUG
				cerr << "orderImp out\n";
				#endif
				return uguale;
			}
		}
	}
}
