#pragma once
#ifndef ALGORYTM_H
#define ALGORYTM_H

#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Zapytania.h"
#include <algorithm>

// ZMIANA ZAMYS�U NA JEDN� D�UG� WEKTOR ZAMIAST 2 Wymiarowej mapy
// ZMIENNE GLOBALNE

class Osobnik { // Zbi�r wszystkich osobnik�w zostanie zapisany jako vector
public:
	std::vector<int> DNA;
	double Fitness=0;  // Im mniejszy fitness tym lepszy 
	int MovesAmount = 1000;
	int CurrentFloor=0;
	void GenerateRandomDNA();
	void Mutate();
	void IsDone(int index);

	std::vector<int> getDNA();
};

#endif

extern Osobnik BestOsobnik;
extern Osobnik BestOsobnik2;
void PrintRandomDNAForPopulation(int);
void CrossoverView(std::vector<Zapytanie>,std::vector<int>&);
void AlgorithmConfiguration();
int  AlgorithmPopulationSize();
void AlgorithmObliczania(std::vector<Zapytanie>, std::vector<int>&, int);
void FitnessSimulationWithElevator(Osobnik& x, std::vector<Zapytanie> newEnquiryVector, int);
void Symulacja2();
std::vector<int> TranslateDNA(Osobnik);
void ClearData();