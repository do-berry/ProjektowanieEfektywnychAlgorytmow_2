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

	this->path = new int[size];
	for (int i = 0; i < size; i++) {
		path[i] = i;
	}

	this->bestSolution = new int[size];
	for (int i = 0; i < size; i++) {
		bestSolution[i] = i;
	}
}

SimulatedAnnealing::~SimulatedAnnealing() {
	delete[]path;
	delete[]bestSolution;
	delete path;
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

/*
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
	prawdopodobienstwo akceptacji:
	rozwazanie z jakim prawdopodobienstwem rozwiazanie nowe jest gorsze od starego
*/
double SimulatedAnnealing::acceptanceProb(int newSolutionCost, int oldSolutionCost, double temp) {
	double result = -((newSolutionCost - oldSolutionCost) / temp);
	return pow(M_E, result);
}

/*
	zamiana losowych miast w sciezce
*/
void SimulatedAnnealing::randomSwap() {
	int a = rand() % size;
	int b = rand() % size;
	while (a == b) {
		b = rand() % size;
	}

	swapValues(path[a], path[b]);
}

/*
	glowny algorytm
*/
void SimulatedAnnealing::execute(int * vertices, int **costs) {
	int iterations = (int)pow((double)size, (double)2) / 4; // liczba iteracji: n^2/4
	cost = sumCosts(path, costs); //  obliczenie kosztu aktualnego rozwiazania

	while (temperature > 0.0001) {
		for (int i = 0; i < iterations; i++) {
			// losowa zamiana i obliczenie kosztu drogi
			randomSwap();
			int tmpCost = sumCosts(path, costs);

			// przymujemy znalezione rozwiazanie jesli koszt jest mniejszy od aktualnie najmniejszego 
			// lub prawdopodobienstwo akceptacji gorszego rozwiazania jest wieksze
			// ma to na celu unikniecie minimum lokalnego
			if (tmpCost < cost || acceptanceProb(tmpCost, cost, temperature) > ((double)rand() / (double)RAND_MAX)) {
				copyArray(path, bestSolution);
				cost = tmpCost;
			}
		}
		
		// obnizanie temperatury
		temperature *= cooling;
	}

	printResult(bestSolution);
}
