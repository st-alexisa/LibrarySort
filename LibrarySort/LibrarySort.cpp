#include <iostream>
#include <fstream>
#include "Librarian.h"

int* ReadArray(std::ifstream& fin, int count)
{
	int* arr = new int[count];
	for (int i = 0; i < count; ++i)
	{
		int value;
		fin >> value;
		arr[i] = value;
	}
	return arr;
}

void Sort(int* arr, int count) 
{
	Librarian<int>* librarian = new Librarian<int>(count);

	librarian->Sort(arr, count);

	delete librarian;
}

int main()
{
	std::ifstream fin("input.txt");
	for (int i = 0; i < 20; ++i) 
	{
		int count;
		fin >> count;
		int* arr = ReadArray(fin, count);
		std::cout << i << " arraySize: " << count << " ";
		Sort(arr, count);
		std::cout << std::endl;
		delete[] arr;
	}

	fin.close();
}