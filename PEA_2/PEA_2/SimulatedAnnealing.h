#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

class SimulatedAnnealing {
private:
	int size; // ile miast
	int cost; // koszt najlepszego rozwiazania
	int * path;
	double temperature = 10000.0; // temperatura obecna
	double cooling = 0.999; // temperatura chodzenia
	void randomSwap();
	void copyArray(int *from, int *to);
	int sumCosts(int *path, int **costs);
	double acceptanceProb(int oldSolutionCost, int newSolutionCost);
	void swapValues(int &first, int &second);

public:
	SimulatedAnnealing(int size);
	~SimulatedAnnealing();

	int * bestSolution; // najlepsze znalezione rozwiazanie
	void printResult(int *path);
	void execute(int * vertices, int **costs);
};

#endif // !SIMULATEDANNEALING_H
