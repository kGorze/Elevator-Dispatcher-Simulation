#ifndef ZAPYTANIA_H
#define ZAPYTANIA_H

#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
//----------------------------------------------------------------------------------
//extern int minFloor;
//extern int maxFloor;
//extern int Floors;
//extern int GlobalID;
//----------------------------------------------------------------------------------

class Zapytanie {
public:
	int ID;
	int MiejsceP;
	int MiejsceD;
	//int CzasO; // Czas Oczekiwania na przysz�o��;
	//int CzasP; // Czas Podr�y na przysz�o��
	bool IsInCar = false;

	//jeden licznik
	//inna funkcja, czas, ka�de zapytanie dostaje timestamp podczas odbioru



	Zapytanie();  // Konstruktor to r�cznego tworzenia zapyta� w menu. Przeka� jaki� oboj�tny argument.
	Zapytanie(int);
	Zapytanie(int,int);

	int getMiejsceP() const;
	int getMiejsceD() const;
	int getID() const;

	void setMiejsceP(const int number);
	void setMiejsceD(const int number);
	void setID(const int number);
};

void fillEnquiryVector(std::vector<Zapytanie>&);
void printVector(const std::vector<Zapytanie>&);
void addEnquiry(std::vector<Zapytanie>&);
void eraseEnquiryByIndex(std::vector<Zapytanie>&, int);

#endif // !ZAPYTANIA_H