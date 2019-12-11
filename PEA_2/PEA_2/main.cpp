#include <iostream>
#include <climits>
#include <windows.h>
#include "Reader.h"
#include "SimulatedAnnealing.h"
#include <chrono> 
#include <cstdlib>
#include <ctime>

using namespace std::chrono;
using namespace std;

int main()
{
	srand(time(NULL));

	char choice;
	Reader * reader;
	SimulatedAnnealing * sa;
	char name[] = "ftv70.txt";
	boolean isRead = false;					// czy graf jest wczytany

	cout << "Menu:" << endl;
	cout << "1. Wczytaj graf" << endl
		<< "2. Wyswietl graf" << endl
		<< "3. Symulowane wyzarzanie" << endl
		<< "0. Wyjscie" << endl;

	do {
		cout << "Twoj wybor: ";
		cin >> choice;
		switch (choice)
		{
		case '1':
			reader = new Reader(name);
			isRead = true;
			break;
		case '2':
			if (!isRead) {
				cout << "Graf nie zostal wczytany." << endl;
			}
			else {
				reader->printTab();
			}
			break;
		case '3':
			if (!isRead) {
				cout << "Graf nie zostal wczytany." << endl;
			}
			else {
				sa = new SimulatedAnnealing(reader->elementsNumber);;
				//auto start = high_resolution_clock::now();
				sa->execute(reader->vertices, reader->tab);
				//auto stop = high_resolution_clock::now();
				//auto duration = duration_cast<milliseconds>(stop - start);
				//cout << duration.count() << endl;
				sa->printResult(sa->bestSolution);
			}
			break;
		case '0':
			break;
		default:
			cout << "Bledny wybor." << endl;
		}
	} while (choice != '0');

	delete reader, sa;
    return 0;
}