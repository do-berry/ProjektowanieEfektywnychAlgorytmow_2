#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

class SimulatedAnnealing {
private:
	int size;
	int delta;
	int cost;
	int * path;
	int * tmpPath;
	double temperature = 10000.0;
public:
	double cool = 0.9999;
	int * bestSolution;
	void randomSwap();
	SimulatedAnnealing(int size);
	~SimulatedAnnealing();
	void copyArray(int *from, int *to);
	void printResult(int *path);
	int sumCosts(int *path, int **costs);
	int * randomPath(int * vertices);
	double acceptanceProb(int oldSolutionCost, int newSolutionCost, double temp);
	void cooling(double coolingRate);
	void swapValues(int &first, int &second);
	double getTemperature(int * vertices, int **costs);
	void execute(int * vertices, int **costs);
};

#endif // !SIMULATEDANNEALING_H
