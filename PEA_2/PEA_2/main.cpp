#include <iostream>
#include <climits>
#include <windows.h>
#include "Reader.h"
#include <chrono> 
using namespace std::chrono;

using namespace std;

int main()
{
	char choice;
	Reader * reader;
	char name[] = "tsp_6.txt";
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
				// TODO
			}
			break;
		case '0':
			break;
		default:
			cout << "Bledny wybor." << endl;
		}
	} while (choice != '0');

	delete reader;
    return 0;
}