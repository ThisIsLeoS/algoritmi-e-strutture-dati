#ifndef EVENTO_H
#define EVENTO_H

#include "tragitto.h" // per l'inclusione di <string> e altro
#include <sstream> // per la f. printStr

struct Veicolo
{
	string targa;
	float velMed; // velocità media
	Tragitto tr; 
};

struct Evento
{
	int timestamp; // traduzione in italiano: "marcatura oraria"
	Veicolo v;
	string printStr(Evento e)
	{
		// nota: in questa f. si converte timestamp da intero a stringa
		string str;
		ostringstream oStSt;
		oStSt << e.timestamp;
		Tappa t = e.v.tr.first();
		// cerr << "velMed == " << e.v.velMed << endl;
		// cerr << "distPrev == " << t.distPrev << endl;
		return str = e.v.targa + " " + oStSt.str() + " " + t.citta;
	}
};

#endif
