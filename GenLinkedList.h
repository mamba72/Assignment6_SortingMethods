/*
Stephen White
002323381
stwhite@chapman.edu
Assignment 4 Registrar's office
Data Structures Section 1
*/
#pragma once

#include "GenListNode.h"
#include <exception>
#include <iostream>

using namespace std;

template <class T>
class GenLinkedList
{
private:
	GenListNode<T>* front;
	GenListNode<T>* back;
	unsigned int size;//this saves memory because the int cant be negative.

public:
	GenLinkedList();
	~GenLinkedList();

	//functions
	void insertFront(T d);
	void insertBack(T d);
	T removeFront();
	T removeBack();
	T deletePos(int pos);//deletes the element at the given position
	int find(T d);
	GenListNode<T>* remove(T d);//the data in the node to search for

	//helper functions
	T getPos(int pos);
	bool isEmpty();
	void printList();
	unsigned int getSize();
	T* toArray();

	friend ostream& operator<<(ostream& fileOut, const GenLinkedList<T>& obj)
	{
		GenListNode<T>* curr = obj.front;

		while (curr != NULL)
		{
			fileOut << curr->data << endl;
			curr = curr->next;
		}
		return fileOut;
	}

};

//this is a struct for throwing a custom exception when the list is empty
struct ListEmptyException : public std::exception
{
	const char* what() const throw ()
	{
		return "This list is empty, cannot remove.";
	}
};

template <class T>
GenLinkedList<T>::GenLinkedList()
{
	size = 0;
	front = NULL;
	back = NULL;
}

template <class T>
GenLinkedList<T>::~GenLinkedList()
{
	//we need to figure this out //(maybe look in book)
	GenListNode<T>* curr = front;
	GenListNode<T>* prev = front;

	while (curr != NULL)
	{
		prev = curr;
		curr = curr->next;

		prev = NULL;
	}
}

//add to the front of the list
template<class T>
void GenLinkedList<T>::insertFront(T d)
{
	GenListNode<T>* node = new GenListNode<T>(d);

	if (isEmpty()) //empty list
		back = node;
	else//list is not empty
	{
		front->prev = node;
		node->next = front;
	}

	front = node;

	size++;
}

//add to the back of the list
template<class T>
void GenLinkedList<T>::insertBack(T d)
{
	GenListNode<T>* node = new GenListNode<T>(d);
	//back->next = 
	if (isEmpty())//empty list
	{
		front = node;
	}
	else//not an empty list
	{
		back->next = node;
		node->prev = back;
	}
	back = node;
	++size;
}

//remove the first element in the list
template<class T>
T GenLinkedList<T>::removeFront()
{
	if (isEmpty())
		throw ListEmptyException();


	GenListNode<T>* ft = front; //ft = frontTemp

	if (size == 1)//if size is one, its the only node in the list
	{
		back = NULL;
	}
	else //theres more than one element in list
	{
		front->next->prev = NULL;
	}

	front = front->next;
	T tmp = ft->data;
	ft->next = NULL;
	delete ft;
	size--;

	return tmp;
}

//remove the last element in the list
template<class T>
T GenLinkedList<T>::removeBack()
{
	if (isEmpty())
		throw ListEmptyException();

	GenListNode<T>* bk = back;

	if (size == 1)
	{
		back = NULL;
	}
	else
	{
		back->prev->next = NULL;
	}

	back = back->prev;
	T tmp = bk->data;
	bk->prev = NULL;
	delete bk;
	size--;

	return tmp;
}

//this can be easily changed to delete a given value, not a given position
template<class T>
T GenLinkedList<T>::deletePos(int pos)
{
	if (pos > size || pos < 0)
		throw runtime_error("Your position is out of bounds of the length of the list.");

	int idx = 0; //index
	GenListNode<T>* curr = front;
	GenListNode<T>* prev = front;//needs to be one behind the current

	while (idx != pos)
	{
		prev = curr;
		curr = curr->next;
		idx++;
	}
	//now curr is in the position that we want to delete
	prev->next = curr->next;
	//now we've skipped over the curr node.
	//now we have to delete it.
	curr->next = NULL;//set next to null to ensure that deleting it doesnt also delete the next node thats being referenced
	T tmp = curr->data;
	delete curr;

	size--;
	return tmp;
}

template<class T>
int GenLinkedList<T>::find(T d)
{
	int idx = 0;
	GenListNode<T>* curr = front;

	while (curr != NULL)//or could do (idx < size)
	{
		if (curr->data == d)
			break;//we found it. now break the loop
		//increment the current node
		curr = curr->next;
		idx++;
	}

	if (curr == NULL)//we didnt find the value in the list
		idx = -1;

	return idx;
}

//removes the element that contains the given data and returns the pointer to that object
template<class T>
GenListNode<T>* GenLinkedList<T>::remove(T d)
{
	if (isEmpty())
		throw ListEmptyException();

	GenListNode<T>* curr = front;

	while (curr->data != d)
	{
		curr = curr->next;

		if (curr == NULL)//we didnt find the value
			return NULL;
	}

	//if we get here, it means we found the node

	//check if node is in the front
	if (curr == front)
	{
		front = curr->next;
	}
	else if (curr == back)//if the node is the back
	{
		curr->prev->next = curr->next;

		back = curr->prev;
	}
	else //its not the front nor back
	{
		curr->prev->next = curr->next;

		curr->next->prev = curr->prev;
	}

	curr->next = NULL;
	curr->prev = NULL;

	size--;

	return curr;
}

//starts at zero. treat it like an array accessor
template<class T>
T GenLinkedList<T>::getPos(int pos)
{
	if (isEmpty())
		throw ListEmptyException();

	GenListNode<T>* curr = front;
	int index = 0;

	while (index != pos)
	{
		curr = curr->next;

		if (curr == NULL)
			return (T)NULL;//cast to type T to prevent throwing warnings
		index++;
	}

	return curr->data;
}

template<class T>
bool GenLinkedList<T>::isEmpty()
{
	if (size == 0)
		return true;
	return false;
}

//print the value of each element
template<class T>
void GenLinkedList<T>::printList()
{
	GenListNode<T>* curr = front;
	while (curr != NULL)
	{
		cout << curr->data << endl;
		curr = curr->next;
	}
}

//return the size or length of the list
template<class T>
unsigned int GenLinkedList<T>::getSize()
{
	return size;
}

//return an array from the list
template<class T>
T* GenLinkedList<T>::toArray()
{
	T* myArray = new T[size];

	unsigned int indexCounter = 0;
	GenListNode<T>* curr = front;
	while (curr != NULL)
	{
		myArray[indexCounter] = curr->data;
		++indexCounter;

		curr = curr->next;
	}

	return myArray;

}

//ostream& operator<<(ostream& fileOut, const GenLinkedList<T>& obj)
//{
//	GenListNode<T>* curr = obj.front;
//
//	while (curr != NULL)
//	{
//		fileOut << curr->data << endl;
//		curr = curr->next;
//	}
//
//
//	return fileOut;
//
//}