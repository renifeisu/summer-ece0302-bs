//  Adapated from Frank M. Carrano and Timothy M. Henry.

/** ADT Stack implementation.
    @file Stack.cpp */

#include <iostream>
#include <cstddef>
#include "Stack.hpp"
#include "Node.hpp"

// TODO: Implement the constructor here
template<class ItemType>
Stack<ItemType>::Stack() 
{
	headPtr = nullptr; // first node pointer points to nothing
	currentSize = 0; // no items
}  // end default constructor

// TODO: Implement the destructor here
template<class ItemType>
Stack<ItemType>::~Stack()
{
	clear(); // pops all items
}  // end destructor

// TODO: Implement the isEmpty method here
template<class ItemType>
bool Stack<ItemType>::isEmpty() const
{
	if(currentSize == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}  // end isEmpty

// TODO: Implement the size method here
template<class ItemType>
int Stack<ItemType>::size() const
{
	return currentSize;
}  // end size

// TODO: Implement the push method here
template<class ItemType>
bool Stack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType> *tempPtr = new Node<ItemType>(newItem, headPtr); // tempPtr points to newItem, and next pointer is headPtr
	headPtr = tempPtr; // tempPtr becomes the new headPtr
	currentSize++;
	return true;
}  // end push

// TODO: Implement the peek method here
template<class ItemType>
ItemType Stack<ItemType>::peek() const
{
	ItemType returnItem; // temp variable that stores the item on the top of the stack
	if(!isEmpty())
	{
		returnItem =  headPtr->getItem(); // first item in stack
	}
	else
	{
		throw std::logic_error("Empty stack");
	}
	return returnItem;
}  // end peek

// TODO: Implement the pop method here
template<class ItemType>
bool Stack<ItemType>::pop() 
{
	if(!isEmpty()) // can only pop if stack has items
	{
		Node<ItemType> *tempPtr = headPtr; // creates tempPtr to point to item in headPtr
		headPtr = headPtr->getNext(); // headPtr points to the next pointer

		tempPtr->setNext(nullptr); // unlinks node from top of the stack
		delete tempPtr; // deletes node that tempPtr is pointing to
		tempPtr = nullptr;
		currentSize--;

		return true;
	}
	else
	{
		return false;
	}
}  // end pop

// TODO: Implement the clear method here
template<class ItemType>
void Stack<ItemType>::clear()
{
	while(!isEmpty())
	{
		pop(); // keep removing first item until no items in stack
	}
}  // end clear

