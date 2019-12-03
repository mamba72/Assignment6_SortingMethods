/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 6 Sorting
*/

#include<iostream>
#include<time.h> //this will be used to time the methods
#include"Sorter.h"

#include<random>

double* readFromFile(string fileName);

int main(int argc, char** argv)
{
	//double* arr = new double[10];
	double arr[] = { 0.5, 0.6, 0.2, 0.5, 0.6, 0.8, 0.001, 1, 0.051, 0.03 };
	double arr2[] = { 0.5, 0.6, 0.2, 0.5, 0.6, 0.8, 0.001, 1, 0.051, 0.03 };
	double arr3[] = { 0.5, 0.6, 0.2, 0.5, 0.6, 0.8, 0.001, 1, 0.051, 0.03 };


	/*for (int i = 0; i < 10; ++i)
	{
		double tmp = rand();
		arr[i] = tmp;
	}*/

	//print the array
	for (int i = 0; i < 10; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;


	Sorter::BubbleSort(arr, 10);


	//print the array
	for (int i = 0; i < 10; ++i)
	{
		cout << arr[i] << " ";
	}
	cout << endl;


	Sorter::SelectionSort(arr2, 10);
	//print the array
	for (int i = 0; i < 10; ++i)
	{
		cout << arr2[i] << " ";
	}
	cout << endl;


	Sorter::InsertionSort(arr3, 10);

	//print the array
	for (int i = 0; i < 10; ++i)
	{
		cout << arr3[i] << " ";
	}
	cout << endl;
}


//returns the double array from the file
double* readFromFile(string fileName)
{

}