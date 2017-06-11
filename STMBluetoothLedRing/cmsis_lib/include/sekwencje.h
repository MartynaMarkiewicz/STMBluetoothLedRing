#ifndef SEKWENCJE_H
#define SEKWENCJE_H

struct zmiana
{
	char r;
	char g;
	char b;
	char dioda;
	int czas;
};

struct sekwencja
{
	struct zmiana zmiany[1000];
	int ilosc;
};

struct ring
{
	struct sekwencja* sekw;
	int czas;
	int index;
	int dioda_od;
};

struct sekwencje
{
	struct sekwencja sekw[6];
};

struct sekwencje Sekwencje;
struct ring Ringi[2];

void ustawSekwencje();
void pokazZmiane();
#endif


