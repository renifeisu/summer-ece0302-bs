#include "limited_size_bag.hpp"

template<typename T>
LimitedSizeBag<T>::LimitedSizeBag() 
{
  itemCount = 0; // bag is initially empty
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
    itemCount ++; // increment number of items
    items[itemCount] = item; // stores item into bag

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
    itemCount--; // decrements the number of items by one

    std::size_t index; // finds the location of item
    for(std::size_t i = 0; i < maxsize; i++)
    {
      if(items[i] == item)
      {
        index = i;
        break;
      }
    }

    // shifting other items in the bag to remove an item
    for(std::size_t i = index; i < maxsize - 1; i++)
    {
      items[i] = items[i + 1];
    }

    return true;
  }
}

template<typename T>
bool LimitedSizeBag<T>::isEmpty() const
{
  if(itemCount < 1) // number of items in the bag has to be zero to be empty
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
  return itemCount; // returns number of items in the bag
}

template<typename T>
bool LimitedSizeBag<T>::contains(const T& item) const
{  
  if(isEmpty()) // bag must have item count > 0 to contain an item
  {
    return false;
  }

  std::size_t check = 0; // checks to see if item is in bag

  for(std::size_t i = 0; i < maxsize; i++)
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
  // resets all values in the array
  for(std::size_t i = 0; i < maxsize; i++)
  {
    items[i] = 0;
  }

  itemCount = 0;
}

template<typename T>
std::size_t LimitedSizeBag<T>::getFrequencyOf(const T & item) const
{
  std::size_t count = 0; // initializes frequency to be zero

  for(std::size_t i = 0; i < maxsize; i++)
  {
    if(items[i] == item)
    {
      count++; // increments count every time loop finds item in bag
    }
  }

  return count;
};
