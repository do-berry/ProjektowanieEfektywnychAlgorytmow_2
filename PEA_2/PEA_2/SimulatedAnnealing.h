#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

class SimulatedAnnealing {
private:
	int size;
	int delta;
	int cost;
	int * path;
	int * tmpPath;
	float temperature;
	int * bestSolution;
public:
	float cool;
	SimulatedAnnealing(int size);
	~SimulatedAnnealing();
	void copyArray(int *from, int *to);
	void printResult(int *path);
	int sumCosts(int *path, int **costs);
	int * randomPath(int * vertices);
	float acceptanceProb(int oldSolutionCost, int newSolutionCost, float temp);
	void cooling(float coolingRate);
	void swapValues(int &first, int &second);
	float getTemperature(int * vertices, int **costs);
	void execute(int * vertices, int **costs);
};

#endif // !SIMULATEDANNEALING_H
