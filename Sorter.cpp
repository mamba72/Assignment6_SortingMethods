/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 6 Sorting
*/

#include "Sorter.h"

//sorting functions:
void Sorter::QuickSort(double* myArray, int arrayLength)
{

}


void Sorter::InsertionSort(double* myArray, int arrayLength)
{
	//insertion sort is on page 110 in text book (134 in pdf)

	for (int j = 1; j < arrayLength; ++j)
	{
		double temp = myArray[j];
		int k = j;

		while (k > 0 && myArray[k - 1] >= temp)
		{
			myArray[k] = myArray[k - 1];
			--k;
		}

		myArray[k] = temp;
	}

}

void Sorter::BubbleSort(double* myArray, int arrayLength)
{
	//bubble sort is on page 259 in text book (283 in pdf)
	//also took a pic of the sudo code

	for (int i = 0; i < arrayLength; ++i)
	{
		double temp = 0;
		//THIS IS DIFFERENT FROM THE POWERPOINT!!
		for (int j = 0; j < arrayLength - 1; ++j)
		{
			if (myArray[j] > myArray[j + 1])
			{
				temp = myArray[j+1];
				myArray[j+1] = myArray[j];
				myArray[j] = temp;
			}
		}
	}

}


void Sorter::MergeSort(double* myArray, int arrayLength)
{
	
}


void Sorter::SelectionSort(double* myArray, int arrayLength)
{
	int i, j, minIndex;
	double tmp;

	for (i = 0; i < arrayLength - 1; ++i)
	{
		minIndex = i;

		for (j = i + 1; j < arrayLength; ++j)
		{
			if (myArray[j] < myArray[minIndex])
				minIndex = j;
		}


		if (minIndex != i)
		{
			tmp = myArray[i];
			myArray[i] = myArray[minIndex];
			myArray[minIndex] = tmp;
		}

	}
}