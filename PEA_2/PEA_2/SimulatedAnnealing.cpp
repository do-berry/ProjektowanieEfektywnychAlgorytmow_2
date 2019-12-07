#include "SimulatedAnnealing.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

using namespace std;

SimulatedAnnealing::SimulatedAnnealing(int size) {
	this->size = size;
	this->cool = 0.999;
	// tworzenie tablic
	this->path = new int[size];
	this->tmpPath = new int[size];
	this->bestSolution = new int[size];
}

SimulatedAnnealing::~SimulatedAnnealing() {
	delete[]path;
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
	cout << "Koszt: " << size << ", sciezka: ";
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
float SimulatedAnnealing::acceptanceProb(int oldSolutionCost, int newSolutionCost, float temp) {
	if (newSolutionCost < oldSolutionCost) {
		return 1.0;
	}
	return exp(-(newSolutionCost - oldSolutionCost) / temp);
}

/*
	ustawienie chlodzenia
	chlodzenie: wspolczynnik alfa podawany przy starcie
*/
void SimulatedAnnealing::cooling(float coolingRate) {
	if (cool > 0 && cool < 1) {
		cool = coolingRate;
	}
}

/*
	obliczanie temperatury poczatkowej na podstawie roznicy drog
*/
float SimulatedAnnealing::getTemperature(int * vertices, int **costs) {
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
	return -(delta) / log(cool);
}

void SimulatedAnnealing::execute(int * vertices, int **costs) {
	temperature = getTemperature(vertices, costs); // poczatkowa temperatura
	path = randomPath(vertices);  // droga poczatkowa
	bestSolution = randomPath(vertices);

	copyArray(path, bestSolution);
	int cost = sumCosts(bestSolution, costs); //  obliczenie kosztu aktualnego rozwiazania

	while (temperature > 0.0001) {
		int x1, x2;

		do {
			x1 = rand() % (size - 1);
			x2 = rand() % (size - 1);
		} while (x1 == x2);

		swap(path[x1], path[x2]);

		int tmpCost = sumCosts(path, costs);
		float chance = rand() / RAND_MAX;

		if (acceptanceProb(cost, tmpCost, temperature) > chance) {
			copyArray(path, bestSolution);
			cost = sumCosts(bestSolution, costs);
		}
		else {
			copyArray(bestSolution, path);
		}
		temperature *= cool;
	}
}
