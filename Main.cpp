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
#include <random>

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

//exception thrown when the file doesnt contain anything
class FileIsEmptyException : public runtime_error
{
public:
	FileIsEmptyException(string msg) : runtime_error(msg.c_str())
	{

	}
};

const string AnalysisFolderName = "Analysis";
const string AnalysisTextFileName = "SortingTimes.txt";

//this is the separator between file names. Just because I'm not sure which one to use
//since its a docker container over windows
const char kPathSeparator =
#ifdef _WIN32
'\\';
#else
'/';
#endif

arrayFromFile* readFromFile(string fileName);
void writeRandomFile(unsigned int numberOfRandoms);

int main(int argc, char** argv)
{

	if (argc != 2)
	{
		cout << "You must enter a file name as well." << endl;
		cout << "If you'd like to randomly generate numbers instead, type \'Random\' instead of a file." << endl;
		return 1;
	}

	//create the time object
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::duration<float> fsec;

	string fileName = argv[1];

	if (fileName == "Random")
	{
		unsigned int numNumbers = 0;
		cout << "Enter the number of random doubles you'd like to create:" << endl;
		cout << "WARNING: if you pull a stupid and put in a negative, it will make an enormous amount of numbers" << endl;
		cin >> numNumbers;

		cout << "Generating random numbers. This can take a while..." << endl;
		writeRandomFile(numNumbers);
		cout << "Finished creating random numbers" << endl;
		fileName = "RandomizedTestFile.txt";
	}
	
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
	catch (FileIsEmptyException e)
	{
		cout << e.what() << endl;
		return 1;
	}
	
	//grab the array from the arrayInfo struct
	double* arrBub = arrayInfo->myArray;
	int arrLength = arrayInfo->arrayLength;

	cout << "The length of the arrays: " << arrLength << endl;

	ofstream outFile;
	string outFileName = AnalysisFolderName + kPathSeparator + AnalysisTextFileName;
	outFile.open(outFileName);

	outFile << "Dataset Size: " << arrLength << endl;

	//cout << "Creating 3 other copies of the array. This might take some time if it is an extremely large dataset." << endl;

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

	double* arrMerge = new double[arrLength];
	for (int i = 0; i < arrLength; ++i)
	{
		arrMerge[i] = arrayInfo->myArray[i];
	}

	cout << "Finished copying arrays." << endl;

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

	//print to the file
	outFile << "Bubble Sort Time Required (seconds): " << seconds.count() << endl;

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

	//print to the file
	outFile << "Selection Sort Time Required (seconds): " << seconds.count() << endl;

	
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

	//print to the file
	outFile << "Insertion Sort Time Required (seconds): " << seconds.count() << endl;


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

	//print to the file
	outFile << "Quick Sort Time Required (seconds): " << seconds.count() << endl;


	//merge sort
	cout << "\nStarting Merge Sort..." << endl;

	//get the start time
	start = chrono::system_clock::now();
	startTime = chrono::system_clock::to_time_t(start);
	cout << "Merge Sort Start Time: " << ctime(&startTime);
	//sort
	Sorter::MergeSort(arrMerge, 0, arrLength - 1);
	//get the end time
	end = chrono::system_clock::now();
	cout << "Finished Merge Sort" << endl;
	endTime = chrono::system_clock::to_time_t(end);
	cout << "End Time: " << ctime(&endTime);
	cout << "Time it took to do Merge sort:" << endl;

	//get the elapsed time
	seconds = end - start;
	cout << seconds.count() << " seconds." << endl;

	//print to the file
	outFile << "Merge Sort Time Required (seconds): " << seconds.count() << endl;

	outFile.close();

	return 0;
}




//returns the double array and array length from the file
arrayFromFile* readFromFile(string fileName)
{
	ifstream file;
	file.open(fileName);

	if (file.is_open() == false)
		throw FileCouldNotBeOpenedException("The file by the name of " + fileName + " could not be opened.");

	string line = "";


	getline(file, line);

	if (line == "")
		throw FileIsEmptyException("File by the name of " + fileName + " is empty.");

	int numNumbers = 0;

	//make sure that the first line can be parsed into an int
	try
	{
		numNumbers = stoi(line);
	}
	catch (invalid_argument e)
	{
		throw FileNotInCorrectFormatException("Your file is not in the correct format.\nIt must start with an int but first line is " + line + ".");
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



void writeRandomFile(unsigned int numberOfRandoms)
{
	srand(time(NULL));

	double num;

	ofstream file;
	file.open("RandomizedTestFile.txt");

	file << numberOfRandoms << endl;

	for (unsigned int i = 0; i < numberOfRandoms; ++i)
	{
		num = (double)rand() / RAND_MAX;
		file << num << endl;
	}

	file.close();
}