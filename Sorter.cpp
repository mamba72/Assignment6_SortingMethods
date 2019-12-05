/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 6 Sorting
*/

#include "Sorter.h"

//sorting functions:

/*
low = starting index
high = ending index
*/
void Sorter::QuickSort(double* myArray, int low, int high)
{

	if (low < high)
	{
		int part = partition(myArray, low, high);

		QuickSort(myArray, low, part - 1);
		QuickSort(myArray, part + 1, high);
	}


}

int Sorter::partition(double* arr, int low, int high)
{
	//select the right most value as the initial partition
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high - 1; ++j)
	{
		if (arr[j] < pivot)
		{
			++i;
			double tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}

	//swap the values
	double tmp = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = tmp;

	return (i + 1);
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


void Sorter::MergeSort(double* myArray, int leftLength, int rightLength)
{
	if (leftLength < rightLength)
	{
		int middle = leftLength + (rightLength - leftLength) / 2;

		//sort first and second halves
		MergeSort(myArray, leftLength, middle);
		MergeSort(myArray, middle + 1, rightLength);

		merge(myArray, leftLength, middle, rightLength);
	}
}

void Sorter::merge(double* arr, int leftLength, int middle, int rightLength)
{
	int n1 = middle - leftLength + 1;
	int n2 = rightLength - middle;

	//create the temp arrays
	double* arrL = new double[n1];
	double* arrR = new double[n2];

	//copy data to the arrays
	for (int i = 0; i < n1; ++i)
	{
		arrL[i] = arr[leftLength + i];
	}
	for (int j = 0; j < n2; ++j)
	{
		arrR[j] = arr[middle + 1 + j];
	}

	//merge the arrays back into the original arr
	int i = 0; //initial index of first array
	int j = 0;//inital index of second array
	int k = leftLength;//initial index of merged array

	while (i < n1 && j < n2)
	{
		if (arrL[i] <= arrR[j])
		{
			arr[k] = arrL[i];
			i++;
		}
		else
		{
			arr[k] = arrR[j];
			j++;
		}
		
		k++;
	}

	//copy the rest of the left array if there is anything
	while (i < n1)
	{
		arr[k] = arrL[i];
		i++;
		k++;
	}

	//copy the rest of the right array if there is anything
	while (j < n2)
	{
		arr[k] = arrR[j];
		j++;
		k++;
	}
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