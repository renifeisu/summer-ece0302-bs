#include "sorted_linked_list.hpp"
#include <stdexcept>

template <typename T>
SortedLinkedList<T>::SortedLinkedList(): LinkedList<T>()
{
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(LinkedList<T> unsorted_list) 
{
  // TODO
  headPtr = nullptr;
  size = 0;

  if(unsorted_list.isEmpty()) // if unsorted list is empty
  {
    // do nothing
  }
  else
  {
    // Copy first node
    headPtr = new Node<T>();
    headPtr->setItem(unsorted_list.getEntry(0));
    size++;

    // Temporary pointer to first node
    Node<T> *tempPtr = headPtr;

    for(int i = 0; i < unsorted_list.getLength(); i++)
    {
      T tempItem = unsorted_list.getEntry(i + 1); // item in node
      Node<T> *newNodePtr = new Node<T>(tempItem); // create new node with item
      tempPtr->setNext(newNodePtr); // links new node
      tempPtr = tempPtr->getNext(); // tempPtr points to next node
      size++;
    }

    tempPtr->setNext(nullptr);

    sort(); // calls the sort function
  }
}

template <typename T>
SortedLinkedList<T>::SortedLinkedList(const SortedLinkedList<T> & x):
  LinkedList<T>(x)
{
}

template <typename T>
SortedLinkedList<T>& SortedLinkedList<T>::operator=(SortedLinkedList<T> x)
{
  LinkedList<T>::operator=(x);
  return *this;
}

template <typename T>
SortedLinkedList<T>::~SortedLinkedList()
{
  // base destructor gets called automatically
}

template <typename T>
bool SortedLinkedList<T>::isEmpty() const noexcept
{
  return LinkedList<T>::isEmpty();
}

template <typename T>
std::size_t SortedLinkedList<T>::getLength() const noexcept
{
  return LinkedList<T>::getLength();
}

template <typename T>
void SortedLinkedList<T>::insert(const T& item)
{
  // TODO
    Node<T> *newNode = new Node<T>(item); // creating new node with item

    newNode->setNext(headPtr); // inserts new node at the beginning of the lsit
    headPtr = newNode;

    size++; // increments size

    sort(); // calls the sort function
}

template <typename T>
void SortedLinkedList<T>::remove(const T& item)
{
  if(isEmpty()) throw std::range_error("empty list in remove");
  
  // TODO
  std::size_t position = getPosition(item);
  removeAt(position);
  
}

template <typename T>
void SortedLinkedList<T>::removeAt(std::size_t position)
{
  if(isEmpty()) throw std::range_error("empty list in remove");
  
  // TODO
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

    sort(); // calls the sort function
  }
}

template <typename T>
void SortedLinkedList<T>::clear()
{
  LinkedList<T>::clear();
}

template <typename T>
T SortedLinkedList<T>::getEntry(std::size_t position) const
{
  return LinkedList<T>::getEntry(position+1);
}

template <typename T>
long int SortedLinkedList<T>::getPosition(const T& item)
{
  // TODO
  long int position = 0;
  Node<T> *tempPtr = headPtr;

  for(int i = 0; i < size; i++)
  {
    if(tempPtr->getItem() == item)
    {
      position = i;
      break;
    }
    else
    {
      tempPtr = tempPtr->getNext();
    }
  }

  return position;
}

template<typename T> 
void SortedLinkedList<T>::sort()
{
	// Selection sorting
	if(getLength() < 2)
	{
		// do nothing
	}
	else
	{
		std::size_t count = 0; // checks to see if any changes to list occurred
		for(std::size_t i = 0; i < getLength() - 1; i ++)
		{
			for(std::size_t j = i + 1; j < getLength(); j++) // finds min value
			{
				T i1 = getEntry(i);
				T i2 = getEntry(j); // tempPtr points to node i + 1
				if(i2 < i1) // if next item is less than current item, swap
				{
					// swap contents
					setEntry(i, i2);
					setEntry(j, i1);
					count++; // increments count
				}
			}
		}
		if(count == 0) // if no shifting happened
		{
			// do nothing 
		}
		else
		{
			sort(); // recursively call this function
		}
	}
}

template <typename T>
void SortedLinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
    Node<T> *positionPtr = headPtr; // temp pointer to find the node at position
    for(std::size_t i = 0; i < position; i++)
    {
      positionPtr = positionPtr->getNext(); // positionPtr points to node at position
    }
    positionPtr->setItem(newValue); // set item at position
}
