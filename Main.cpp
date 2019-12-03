/*
Stephen White
002323381
stwhite@chapman.edu
Data Structures Section 1
Assignment 6 Sorting
*/

#include<iostream>
#include<time.h> //this will be used to time the methods
#include<chrono>
#include <ctime>
#include"Sorter.h"
#include <fstream>
#include <string>

using namespace std;

struct arrayFromFile
{
	double* myArray;
	int arrayLength;
};

//exception thrown when the file cant be opened
class FileCouldNotBeOpenedException : public runtime_error
{
public:
	FileCouldNotBeOpenedException(string msg) : runtime_error(msg.c_str())
	{

	}
};

//exception thrown when the file contains things that arent numbers
class FileNotInCorrectFormatException : public runtime_error
{
public:
	FileNotInCorrectFormatException(string msg) : runtime_error(msg.c_str())
	{

	}
};

arrayFromFile* readFromFile(string fileName);

int main(int argc, char** argv)
{

	if (argc != 2)
	{
		cout << "You must enter a file name as well." << endl;
		return 1;
	}

	string fileName = argv[1];

	//create the time object
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;

	//start all that jazz


	cout << "Reading from the file." << endl;
	arrayFromFile* arrayInfo;
	try
	{
		arrayInfo = readFromFile(fileName);
	}
	catch (FileCouldNotBeOpenedException e)
	{
		cout << e.what() << endl;
		return 1;
	}
	catch (FileNotInCorrectFormatException e)
	{
		cout << e.what() << endl;
		return 1;
	}
	

	double* arrBub = arrayInfo->myArray;
	int arrLength = arrayInfo->arrayLength;

	cout << "The length of the arrays: " << arrLength << endl;

	cout << "Creating 3 other copies of the array. This might take some time if it is an extremely large dataset." << endl;

	double* arrSelect = new double[arrLength];
	//creating a copy of the original array because otherwise all the sorting will be done by the first function
	for (int i = 0; i < arrLength; ++i)
	{
		arrSelect[i] = arrayInfo->myArray[i];
	}

	double* arrInsert = new double[arrLength];
	for (int i = 0; i < arrLength; ++i)
	{
		arrInsert[i] = arrayInfo->myArray[i];
	}

	double* arrQuick = new double[arrLength];
	for (int i = 0; i < arrLength; ++i)
	{
		arrQuick[i] = arrayInfo->myArray[i];
	}

	cout << "Finished copying arrays." << endl;


	//print the array
	for (int i = 0; i < 10; ++i)
	{
		cout << arrBub[i] << " ";
	}
	cout << endl;

	//bubble sort
	cout << "\nStarting Bubble Sort..." << endl;
	
	//get the start time
	auto start = chrono::system_clock::now();
	std::time_t startTime = chrono::system_clock::to_time_t(start);
	cout << "Bubble Sort Start Time: " << ctime(&startTime);
	//sort
	Sorter::BubbleSort(arrBub, arrLength);
	//get the end time
	auto end = chrono::system_clock::now();
	cout << "Finished Bubble Sort" << endl;
	std::time_t endTime = chrono::system_clock::to_time_t(end);
	cout << "End Time: " << ctime(&endTime);
	cout << "Time it took to do bubble sort:" << endl;
	
	//get the elapsed time
	fsec seconds = end - start;
	cout << seconds.count() << " seconds." << endl;

	//selection sort
	cout << "\nStarting Selection Sort..." << endl;
	//get the starting time
	start = chrono::system_clock::now();
	//convert the start time to a time_t?
	startTime = chrono::system_clock::to_time_t(start);
	cout << "Selection Sort Start Time: " << ctime(&startTime);

	Sorter::SelectionSort(arrSelect, arrLength);
	end = chrono::system_clock::now();
	cout << "Finished Selection Sort" << endl;

	endTime = chrono::system_clock::to_time_t(end);
	cout << "End Time: " << ctime(&endTime);
	cout << "Time it took to do Selection sort:" << endl;
	seconds = end - start;

	cout << seconds.count() << " seconds." << endl;

	
	//insertion sort
	cout << "\nStarting Insertion Sort..." << endl;
	start = chrono::system_clock::now();

	startTime = chrono::system_clock::to_time_t(start);
	cout << "Insertion Sort Start Time: " << ctime(&startTime);

	Sorter::InsertionSort(arrInsert, arrLength);
	end = chrono::system_clock::now();
	cout << "Finished Insertion Sort" << endl;

	endTime = chrono::system_clock::to_time_t(end);
	cout << "End Time: " << ctime(&endTime);

	cout << "Time it took to do Insertion sort:" << endl;
	seconds = end - start;

	cout << seconds.count() << " seconds." << endl;


	//quicksort
	cout << "\nStarting Quick Sort..." << endl;

	//get the start time
	start = chrono::system_clock::now();
	startTime = chrono::system_clock::to_time_t(start);
	cout << "Quick Sort Start Time: " << ctime(&startTime);
	//sort
	Sorter::QuickSort(arrQuick, 0, arrLength - 1);
	//get the end time
	end = chrono::system_clock::now();
	cout << "Finished Quick Sort" << endl;
	endTime = chrono::system_clock::to_time_t(end);
	cout << "End Time: " << ctime(&endTime);
	cout << "Time it took to do Quick sort:" << endl;

	//get the elapsed time
	seconds = end - start;
	cout << seconds.count() << " seconds." << endl;


	return 0;
}




//returns the double array from the file
arrayFromFile* readFromFile(string fileName)
{
	ifstream file;
	file.open(fileName);

	if (file.is_open() == false)
		throw FileCouldNotBeOpenedException("The file by the name of " + fileName + " could not be opened.");

	string line = "";

	getline(file, line);

	int numNumbers = 0;

	//make sure that the first line can be parsed into an int
	try
	{
		numNumbers = stoi(line);
	}
	catch (invalid_argument e)
	{
		throw FileNotInCorrectFormatException("Your file is not in the correct format.\nIt must start with an int but first line is " + line);
	}

	//create the array with the given length from the file
	double* arr = new double[numNumbers];

	//read in all the numbers
	for (int i = 0; i < numNumbers; ++i)
	{
		if (file.eof() == true)
			throw FileNotInCorrectFormatException("The given number of numbers does not match the length of the file.");

		getline(file, line);
		//make sure that the line is a number
		try
		{
			arr[i] = stod(line);
		}
		catch (invalid_argument e)
		{
			throw FileNotInCorrectFormatException("Your file is not in the correct format.\nIt must start with an int but first line is " + line);
		}
	}

	//make sure to close the file
	file.close();

	//build the struct.
	arrayFromFile* clump = new arrayFromFile();

	clump->arrayLength = numNumbers;
	clump->myArray = arr;

	//return the struct containing the length of the array and the array
	return clump;

}

