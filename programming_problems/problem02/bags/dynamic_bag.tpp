#include "dynamic_bag.hpp"

template<typename T>
DynamicBag<T>::DynamicBag() 
{
  itemCount = 0; // bag is initially empty
  items = nullptr; // set item pointer to null
}
  

template<typename T>
DynamicBag<T>::DynamicBag(const DynamicBag<T>& x)
{
  itemCount = x.itemCount; // sets size of bag to that of Bag x

  if(isEmpty() || itemCount < 0)
  {
    items = nullptr;
  }
  else
  {
    items = new T[itemCount]; // array of size of Bag x is created

    for(std::size_t i = 0; i < itemCount; i++)
    {
      items[i] = x.items[i]; // fills bag with items in Bag x
    }
  }
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

  itemCount = x.itemCount; // sets size of bag to that of Bag x

  items = new T[itemCount]; // array of size of Bag x is created
  
  for(std::size_t i = 0; i < itemCount; i++)
  {
    items[i] = x.items[i]; // fills bag with items in Bag x
  }
  return *this;
}

template<typename T>
void DynamicBag<T>::swap(DynamicBag<T>& x)
{
  DynamicBag<T> tempBag(x); // creates a temporary bag that copies information from Bag x
  x = *this;
  *this = tempBag;
}

template<typename T>
bool DynamicBag<T>::add(const T& item)
{
  itemCount++; // increase size of bag by one

  T *newItems = new T[itemCount]; // creates temporary new array of items

  for(std::size_t i = 0; i < itemCount - 1; i++)
  {
    newItems[i] = items[i]; // copies items from original array into new array
  }
  newItems[itemCount - 1] = item; // adds new item to new array

  delete []items; // deallocates original item array
  items = new T[itemCount];
  for(std::size_t i = 0; i < itemCount; i++)
  {
    items[i] = newItems[i]; // copies items from new array into original array
  }

  return true;
}

template<typename T>
bool DynamicBag<T>::remove(const T& item)
{
  if(contains(item) == false) // bag can't be empty and item needs to exist
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
    if(itemCount - 1 < 1) // removing an item from a bag of size one will make it empty
    {
      newItems = nullptr;
    }
    else
    {
      for(std::size_t i = 0; i < index; i++)
      {
        newItems[i] = items[i];
      }
    }

    // if the index value is not itemCount - 1, or if the item to be removed is not at the end of the items array, have to shift the other items
    if(index < itemCount - 1)
    {
      for(std::size_t i = index; i < itemCount - 1; i++)
      {
        newItems[i] = items[i + 1];
      }
    }

    itemCount--;
    delete []items; // deallocates items array
    items = new T[itemCount]; 
    for(std::size_t i = 0; i < itemCount; i++) // original copies information from new items array
    {
      items[i] = newItems[i];
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
    std::size_t check = 0;
    for(std::size_t i = 0; i < itemCount; i++) // using for loop to iterate through items array to check if any elements match the item being checked
    {
      if(items[i] == item)
      {
        check = 1;
      }
    }
    
    if(check == 0)
    {
      return false;
    }
    else
    {
      return true;
    }
  }

}

template<typename T>
void DynamicBag<T>::clear() 
{
  delete []items; // deallocates items array
  itemCount = 0; // set size of bag to zero
  items = nullptr;
}

template<typename T>
std::size_t DynamicBag<T>::getFrequencyOf(const T & item) const
{
  std::size_t count = 0; // creates variable to store frequency of item, initial count = 0
 
  for(std::size_t i = 0; i < itemCount; i++)
  {
    if(items[i] == item) 
    {
      count++; // increment count every time element in items array matches the item being checked
    }
  }

  return count;
};
