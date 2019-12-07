#include "SimulatedAnnealing.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <cmath>

#define M_E 2.71828182845904523536

using namespace std;

SimulatedAnnealing::SimulatedAnnealing(int size) {
	this->size = size;
	// tworzenie tablic
	this->path = new int[size];
	this->tmpPath = new int[size];
	this->bestSolution = new int[size];
	for (int i = 0; i < size; i++) {
		path[i] = i;
	}
	for (int i = 0; i < size; i++) {
		bestSolution[i] = i;
	}
}

SimulatedAnnealing::~SimulatedAnnealing() {
	delete[]path;
	delete[]bestSolution;
	delete path, tmpPath;
}

/*
	kopiowanie tablicy
*/
void SimulatedAnnealing::copyArray(int *from, int *to)
{
	for (int i = 0; i < size; i++)
	{
		from[i] = to[i];
	}
}

/*
	zamiana wartosci
*/
void SimulatedAnnealing::swapValues(int &first, int &second)
{
	int copy = first;
	first = second;
	second = copy;
}

/*s\
	suma kosztow sciezki
*/
int SimulatedAnnealing::sumCosts(int *path, int **costs) {
	int sum = 0;
	for (int i = 1; i < size; i++)
	{
		sum += costs[path[i - 1]][path[i]];
	}
	sum += costs[path[size - 1]][path[0]];
	return sum;
}

/*
	wypisanie wyniku
*/
void SimulatedAnnealing::printResult(int *path) {
	cout << "Koszt: " << cost << ", sciezka: ";
	for (int i = 0; i < size; i++)
	{
		cout << path[i] << "->";
	}
	cout << path[0] << endl;
}

/*
	wylosowanie sciezki z uwzglednieniem utworzenia cyklu Hamiltona
*/
int * SimulatedAnnealing::randomPath(int * vertices) {
	// zaden z wierzcholkow nie jest odwiedzony
	bool * visited = new bool[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false;
	}

	// tworzenie nowej trasy: losowanie wierzcholka
	// i sprawdzenie czy jest juz uwzgledniony w trasie
	int * path = new int[size];
	int counter = 0, index;
	do {
		index = rand() % size;
		if (!visited[index]) { // jesli nie byl odwiedzony
			visited[index] = true;
			path[counter] = index;
			counter++;
		}
	} while (counter < size);

	delete[] visited;
	return path;
}

/*
	prawdopodobienstwo akceptacji:
	koszt nowego < koszt starego: zwracanie 1.0, pelne zaakceptowanie rozwiazania
	w przeciwnym razie:
	rozwazanie z jakim prawdopodobienstwem rozwiazanie nowe jest gorsze od starego,
	prawdopodobiestwo wyboru gorszej propozycji jest tym mniejsze
	im roznica miedzy proponowanym a starym rozwiazaniem jest wieksza
*/
double SimulatedAnnealing::acceptanceProb(int newSolutionCost, int oldSolutionCost, double temp) {
	/*if (newSolutionCost < oldSolutionCost) {
		return 1.0;
	}
	return exp(-(newSolutionCost - oldSolutionCost) / temp);*/
	double result = -((newSolutionCost - oldSolutionCost) / temp);
	return pow(M_E, result);
}

/*
	ustawienie chlodzenia
	chlodzenie: wspolczynnik alfa podawany przy starcie
*/
void SimulatedAnnealing::cooling(double coolingRate) {
	if (cool > 0 && cool < 1) {
		cool = coolingRate;
	}
}

void SimulatedAnnealing::randomSwap() {
	int a = rand() % size;
	int b = rand() % size;
	while (a == b) {
		b = rand() % size;
	}

	swapValues(path[a], path[b]);
}

/*
	obliczanie temperatury poczatkowej na podstawie roznicy drog
*/
double SimulatedAnnealing::getTemperature(int * vertices, int **costs) {
	path = randomPath(vertices);
	int newCost = sumCosts(path, costs);
	int min = newCost, max = newCost;

	int n = 0;
	while (n++ < pow(size, 2)) {
		int x1, x2;
		do {
			x1 = rand() % (size - 1);
			x2 = rand() % (size - 1);
		} while (x1 == x2);

		swap(path[x1], path[x2]);
		newCost = sumCosts(path, costs);

		if (newCost > max) {
			max = newCost;
		}
		if (newCost < min) {
			min = newCost;
		}
	}

	delta = max - min;
	return (-(delta) / log(cool));
}

void SimulatedAnnealing::execute(int * vertices, int **costs) {
	int x = (int)pow((double)size, (double)2) / 4;
	// temperature = getTemperature(vertices, costs); // poczatkowa temperatura
	//copyArray(vertices, path);
	// printResult(path);
	// path = randomPath(vertices);  // droga poczatkowa
	//bestSolution = randomPath(vertices);
	//copyArray(path, bestSolution);

	cost = sumCosts(path, costs); //  obliczenie kosztu aktualnego rozwiazania

	while (temperature > 0.0001) {
		for (int i = 0; i < x; i++) {
			// losowa zamiana
			randomSwap();
			int tmpCost = sumCosts(path, costs);
			// double chance = ((double)rand() / (RAND_MAX));

			if (tmpCost < cost || acceptanceProb(tmpCost, cost, temperature) > ((double)rand() / (double)RAND_MAX)) {
				copyArray(path, bestSolution);
				cost = tmpCost;
			}
		}
		temperature *= cool;
	}
}
