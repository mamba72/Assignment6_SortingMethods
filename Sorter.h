/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 6 Sorting
*/

#include<iostream>
using namespace std;

class Sorter
{
	static int partition(double* arr, int low, int high);
	static void merge(double* arr, int leftLength, int middle, int rightLength);
	//sort functions
public:
	static void QuickSort(double* myArray, int low, int high);
	static void InsertionSort(double* myArray, int arrayLength);
	static void BubbleSort(double* myArray, int arrayLength);
	static void MergeSort(double* myArray, int leftLength, int rightLength);
	static void SelectionSort(double* myArray, int arrayLength);
};

//this class is used to signify that the user has tried to sort an aray that was empty
class ArrayIsEmptyException : public runtime_error
{
public:
	ArrayIsEmptyException(string msg) : runtime_error(msg.c_str())
	{}
};