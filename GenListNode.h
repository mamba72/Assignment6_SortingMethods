/*
Stephen White
002323381
stwhite@chapman.edu
Assignment 4 Registrar's office
Data Structures Section 1
*/
#pragma once

using namespace std;

template <class T>
class GenListNode
{
public:
	T data;
	GenListNode* next;
	GenListNode* prev;

	//constructor
	GenListNode();
	GenListNode(T d);
	~GenListNode();
};

template<class T>
 GenListNode<T>::GenListNode()
{

}

template<class T>
 GenListNode<T>::GenListNode(T d)
{
	data = d;
	next = nullptr; //NULL;
	prev = nullptr;//NULL;
}

template<class T>
 GenListNode<T>::~GenListNode()
{
	next = nullptr;//NULL;
	prev = nullptr;//NULL;
}
