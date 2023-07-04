#include "linked_list.hpp"

template <typename T>
LinkedList<T>::LinkedList()
{
  //TODO
  headPtr = nullptr; // initializes headPtr
  size = 0; // list is empty
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  //TODO
  // deletes all items
  clear();
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& x)
{
  //TODO
  // Initialize values
  headPtr = nullptr;
  size = 0;

  // Starts with the same headptr as list x
  Node<T> *xheadPtr = x.headPtr;

  if(xheadPtr == nullptr) // if list x is empty
  {
    headPtr = nullptr; 
  }
  else
  {
    // Copy first node
    headPtr = new Node<T>();
    headPtr->setItem(xheadPtr->getItem());
    size++;

    // Temporary pointer to first node
    Node<T> *tempPtr = headPtr;

    // x headPtr points to the next node
    xheadPtr = xheadPtr->getNext();

    while(xheadPtr != nullptr)
    {
      T tempItem = xheadPtr->getItem(); // item in node
      Node<T> *newNodePtr = new Node<T>(tempItem); // create new node with item
      tempPtr->setNext(newNodePtr); // links new node
      tempPtr = tempPtr->getNext(); // tempPtr points to next node
      xheadPtr = xheadPtr->getNext(); // xheadPtr points to next node
      size++;
    }

    tempPtr->setNext(nullptr);
  }
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> x)
{
  //TODO
  LinkedList<T> tempList(x); // temporary list
  swap(tempList);
  return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList& x) 
{
  //TODO
  std::swap(headPtr, x.headPtr);
  std::swap(size, x.size);
}

template <typename T>
bool LinkedList<T>::isEmpty() const noexcept
{
  //TODO
  // list is empty if size = 0
  if(getLength() == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <typename T>
std::size_t LinkedList<T>::getLength() const noexcept
{
  //TODO
  return size;
}

template <typename T>
void LinkedList<T>::insert(std::size_t position, const T& item)
{
  //TODO
  /** Edge case: position cannot be negative or greater than the size of the list*/
  if((position < 0) || (position > size))
  {
    throw std::range_error("Out of range");
  }
  else
  {
    Node<T> *newNode = new Node<T>(item); // creating new node with item

    if(position == 0) // inserting item at beginning of list
    {
      newNode->setNext(headPtr);
      headPtr = newNode;
    }
    else
    {
      Node<T>* beforePtr = headPtr; // temp pointer to find the node before inserting 
      for(std::size_t i = 0; i < position - 1; i++)
      {
        beforePtr = beforePtr->getNext(); // beforePtr points to node position - 1
      }
      // linking nodes
      newNode->setNext(beforePtr->getNext());
      beforePtr->setNext(newNode);
    }
    size++; // increments size
  }
}

template <typename T>
void LinkedList<T>::remove(std::size_t position)
{
  //TODO
  /** Edge case: position cannot be negative or greater than the size of the list*/
  /** list cannot be empty either*/
  if((position < 0) || (position > size - 1) || isEmpty())
  {
    throw std::range_error("Out of range");
  }
  else
  {
    Node<T> *tempPtr = nullptr; // temporary node ptr

    if(position == 0) // remove first item
    {
      tempPtr = headPtr;
      headPtr = headPtr->getNext();
    }
    else
    {
      Node<T> *beforePtr = headPtr; // temp pointer to find the node before removing
      for(std::size_t i = 0; i < position - 1; i++)
      {
        beforePtr = beforePtr->getNext(); // beforePtr points to node position - 1
      }
      // link the nodes before and after the one being removed
      tempPtr = beforePtr->getNext();
      beforePtr->setNext(tempPtr->getNext());
    }
    // deallocating tempPtr memory
    tempPtr->setNext(nullptr);
    delete tempPtr;
    tempPtr = nullptr;
    size--; // decrements size
  }
}

template <typename T>
void LinkedList<T>::clear()
{
  //TODO
  while(!isEmpty())
   {
    remove(0); // keep removing first item
   }
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position) const
{
  //TODO
  /** Edge case: position cannot be negative or greater than the size of the list*/
  /** list cannot be empty*/
  if((position < 0) || (position > size - 1) || (isEmpty()))
  {
    throw std::range_error("Out of range");
  }
  else
  {
    Node<T> *positionPtr = headPtr; // temp pointer to find the node at position
    for(std::size_t i = 0; i < position; i++)
    {
      positionPtr = positionPtr->getNext(); // positionPtr points to node at position
    }
    return positionPtr->getItem(); // return item at position
  }
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
  //TODO
  /** Edge case: position cannot be negative or greater than the size of the list*/
  /** list cannot be empty*/
  if((position < 0) || (position > size - 1) || (isEmpty()))
  {
    throw std::range_error("Out of range");
  } 

  else
  {
    Node<T> *positionPtr = headPtr; // temp pointer to find the node at position
    for(std::size_t i = 0; i < position; i++)
    {
      positionPtr = positionPtr->getNext(); // positionPtr points to node at position
    }
    positionPtr->setItem(newValue); // set item at position
  }
}
