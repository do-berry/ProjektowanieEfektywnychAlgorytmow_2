#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

class SimulatedAnnealing {
private:
	int size; // ile miast
	int cost; // kosz najlepszego rozwiazania
	int * path;
	int * bestSolution; // najlepsze znalezione rozwiazanie
	double temperature = 10000.0; // temperatura poczatkowa
	double cooling = 0.9999; // temperatura chodzenia
	void randomSwap();
	void copyArray(int *from, int *to);
	void printResult(int *path);
	int sumCosts(int *path, int **costs);
	double acceptanceProb(int oldSolutionCost, int newSolutionCost, double temp);
	void swapValues(int &first, int &second);

public:
	SimulatedAnnealing(int size);
	~SimulatedAnnealing();

	void execute(int * vertices, int **costs);
};

#endif // !SIMULATEDANNEALING_H
