//FONDA CHAU 15954143
#pragma once
#include <iostream>
using namespace std;
#ifndef   __node__
#define   __node__


template <class T>
class node {
public:

	T value;
	node *next;
};


/*
struct node {
	int value;
	node *next;
};
*/
template <class T>
class List {
private:
	node<T> *first;
	node<T> *last;

public:
	List();// default constructor sets ptr to null 
	~List();
	void Insert(T x);// add a new node to the end of the list 
	void Delete();// delete a node at the end 
	void Deletefirst();// delete a node at the end 
	T Get(int index);// get some data from the list e.g. 5th item etc 
	void PrintList();// print all data nodes in the list
	int NumberofNodes();

};
template <class T>
List<T>::List() {
	first = NULL;
	last = NULL;
}
template <class T>
List<T>::~List() {//delete all nodes
	while (first != NULL) {
		Delete();
	}

}

template <class T>
int List<T>::NumberofNodes() {
	int count=0;
	node<T> *temp1 = first;
	node<T> *temp = first;

	if (first == NULL) {
	}
	else {
		count = 1;
		if (first->next != NULL) {

			while (temp->next != NULL) {

				temp = temp->next;
				count++;
			}
		}
	}
	return count;

}
template <class T>
void List<T>::Insert(T x) {

	node<T> *newnode = new node<T>;
	newnode->value = x;
	newnode->next = NULL;
	if (first == NULL) {
		first = newnode;
		last = newnode;
	}
	else {
		last->next = newnode;
		last = newnode;
	}
}
template <class T>
void List<T>::Delete() {
	node<T> *temp1 = first;
	node<T> *temp = first;
	if (first == NULL) {
	}
	else if (first->next != NULL) {
		while (temp->next != NULL) {
			temp1 = temp;
			temp = temp1->next;
		}
		delete temp;
		temp1->next = NULL;
	}
	else if (first != NULL) {
		delete first;
		first = NULL;
	}

}
template <class T>
void List<T>::Deletefirst() {
	node<T> *temp1 = first;
	node<T> *temp = first;
	if (first == NULL) {
	}
	else if (first != NULL) {
		temp = first->next;
		delete first;
		first = temp;
	}

}

template <class T>
T List<T>::Get(int index) {
	node<T> *temp = first;
	for (int x = 0; x < index; x++) {
		temp = temp->next;
		if (temp == NULL) {
			return NULL;
		}

	}
	return temp->value;

}
template <class T>
void List<T>::PrintList() {
	node<T> *temp = first;
	int index = 0;

	if (first == NULL) {
		cout << "no node to print\n" << endl;
	}
	else if (first->next != NULL) {
		while (temp->next != NULL) {
			cout << "node with index" << index << ", has data " << temp->value << endl;
			temp = temp->next;
			index++;
		}
		cout << "the last node of index" << index << ", has data " << temp->value << endl;
	}
}
#endif