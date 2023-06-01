#include "limited_size_bag.hpp"

template<typename T>
LimitedSizeBag<T>::LimitedSizeBag() 
{
  itemCount = 0; // bag is initially empty
  items = nullptr; 
}
  
template<typename T>
bool LimitedSizeBag<T>::add(const T& item)
{
  if(itemCount >= maxsize) // bag cannot go over size limit
  {
    return false;
  }
  else
  {
    itemCount ++; // increment size of bag
    T *newItems = new T[itemCount]; // temporary item array
    for(std::size_t i = 0; i < itemCount - 1; i++) // copies original array values into new one
    {
      newItems[i] = items[i];
    }
    newItems[itemCount - 1] = item; // appends an item to new array

    delete []items; // deallocate old array

    items = new T[itemCount]; // make old array same size as new array
    for(std::size_t i = 0; i < itemCount; i++) // copies new array values into old one
    {
      items[i] = newItems[i];
    }

    return true;
  }
}

template<typename T>
bool LimitedSizeBag<T>::remove(const T& item)
{
  if(contains(item) == false) // item needs to exist for it to be removed
  {
    return false;
  }

  else if(itemCount == 1) // if an item is removed from a bag of size one, it will become empty
  {
    clear();
    return true;
  }

  else
  {
    std::size_t index; // identifies the position of the item in bag
    for(std::size_t i = 0; i < itemCount; i++) // for loop to find the index
    {
      if(items[i] == item)
      {
        index = i;
        break;
      }
    }
    
    itemCount--; // decrements the size of the bag

    if(index == itemCount) // if the item is at the end of the bag array, no shifting is needed
    {
      T *newItems = new T[itemCount]; // temporary bag array
      for(std::size_t i = 0; i < itemCount; i++) // temp bag array copies original bag array
      {
        newItems[i] = items[i];
      }

      delete []items; // deallocates memory of original bag array
      items = new T[itemCount]; // resizing original bag array
      for(std::size_t i = 0; i < itemCount; i++) // origianl bag array copies temp bag array
      {
        items[i] = newItems[i];
      }
    }
    else // shifting needed
    {
      T *newItems = new T[itemCount]; // temporary bag array
      for(std::size_t i = 0; i < index; i++) // temp bag array copies original bag array
      {
        newItems[i] = items[i];
      }
      for(std::size_t i = index; i < itemCount; i++) 
      {
        newItems[i] = items[i + 1];
      }

      delete []items; // deallocates memory of original bag array
      items = new T[itemCount]; // resizing original bag array
      for(std::size_t i = 0; i < itemCount; i++) // origianl bag array copies temp bag array
      {
        items[i] = newItems[i];
      }
    }

    return true;
  }
}

template<typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  if(itemCount < 1) // size of bag has to be zero to be empty
  {
    return true;
  }
  else
  {
    return false;
  }
}

template<typename T>
std::size_t LimitedSizeBag<T>::getCurrentSize() const
{
  return itemCount; // return size of bag
}

template<typename T>
bool LimitedSizeBag<T>::contains(const T& item) const
{  
  if(isEmpty()) // bag must have size > 0 to contain an item
  {
    return false;
  }

  std::size_t check = 0; // checks to see if item is in bag

  for(std::size_t i = 0; i < itemCount; i++)
  {
    if(items[i] == item)
    {
      check = 1;
    }
  }

  if(check == 1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template<typename T>
void LimitedSizeBag<T>::clear()
{
  delete []items; // deallocates memory of bag
  itemCount == 0; // sets size of bag to be zero
  items = nullptr; // empty array
}

template<typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T & item) const
{
  std::size_t count = 0; // initializes frequency to be zero

  for(std::size_t i = 0; i < itemCount; i++)
  {
    if(items[i] == item)
    {
      count++; // increments count every time loop finds item in bag
    }
  }

  return count;
};
