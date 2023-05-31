#include "dynamic_bag.hpp"

template<typename T>
DynamicBag<T>::DynamicBag() 
{
  itemCount = 0; // bag is initially empty
  items = new T[size]; // array of size 0 is created
}
  

template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T>& x)
{
  *this = x; // copies information from Bag x into this bag
}
    
template<typename T>
DynamicBag<T>::~DynamicBag(){
  delete []items; // deallocates memory of bag
  items = NULL;
}
  
template<typename T>
DynamicBag<T>& DynamicBag<T>::operator=(DynamicBag<T> x)
{  
  clear(); // clears current bag
  itemCount = x.getCurrentSize(); // sets size of bag to that of Bag x
  items = new T[itemCount]; // array of size of Bag x is created
  for(std::size_t i; i < itemCount; i++)
  {
    items[i] = x.items[i]; // fills bag with items in Bag x
  }
  return *this;
}

template<typename T>
void DynamicBag<T>::swap(DynamicBag<T>& x)
{
  DynamicBag<T> tempBag(x); // creates a temporary bag that copies information from Bag x
  x = this;
  *this = tempBag;
}

template<typename T>
bool DynamicBag<T>::add(const T& item)
{
  itemCount++; // increase size of bag by one
  T *newItems = size[itemCount]; // creates temporary new array of items
  for(std::size_t i = 0; i < itemCount - 1; i++)
  {
    newItems[i] = items[i]; // copies items from original array into new array
  }
  newItems[itemCount - 1] = item; // adds new item to new array
  delete []items; // deallocates original item array
  items = newItems; // copies the information from newItems to items array
  return true;
}

template<typename T>
bool DynamicBag<T>::remove(const T& item)
{
  if((isEmpty() == false) && (contains(item) == false)) // bag can't be empty and item needs to exist
  {
    return false;
  }

  else
  {
    std::size_t index; // creates variable to store index of item when it first appears in the items array
    for(std::size_t i = 0; i < itemCount; i++)
    {
      if(items[i] == item)
      {
        index = i; // stores index of item when it first appears, using the for loop
        break;
      }
    }

    T *newItems = new T[itemCount - 1]; // temporary new item array
    
    // this for loop copies information from items array to new items array up until it reaches the index
    for(std::size_t i = 0; i < index; i++)
    {
      newItems[i] = items[i];
    }

    // if the index value is not itemCount - 1, or if the item to be removed is not at the end of the items array, have to shift the other items
    if(index < itemCount - 1)
    {
      for(std::size_t i = index; i < itemCount - 1; i++)
      {
        newItems[i] = items[i + 1];
      }
    }
  }

  return true;
}

template<typename T>
bool DynamicBag<T>::isEmpty() const
{
  if(itemCount == 0) // bag is only empty if there is no items
  {
    return true;
  }
  else
  {
    return false;
  }
}

template<typename T>
std::size_t DynamicBag<T>::getCurrentSize() const
{
  return itemCount; // current number of items in bag
}

template<typename T>
bool DynamicBag<T>::contains(const T& item) const
{  
  if(isEmpty()) // bag can't be empty
  {
    return false;
  }
  else
  {
    for(std::size_t i; i < itemCount; i++) // using for loop to iterate through items array to check if any elements match the item being checked
    {
      if(items[i] == item)
      {
        return true;
      }
    }
  }

  return false;
}

template<typename T>
void DynamicBag<T>::clear() 
{
  DynamicBag<T> emptyBag(); // creates a temporary bag of size 0
  *this = emptyBag; // copies information from empty bag
}

template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const
{
  std::size_t count = 0; // creates variable to store frequency of item, initial count = 0
 
  for(std::size_t i; i < itemCount; i++)
  {
    if(items[i] == item) 
    {
      count++; // increment count every time element in items array matches the item being checked
    }
  }

  return count;
};
