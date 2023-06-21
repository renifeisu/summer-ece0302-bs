#include "array_list.hpp"

template <typename T>
  ArrayList<T>::ArrayList() {
  // list is initially empty
  array = nullptr;
  length = 0;
}

template <typename T>
ArrayList<T>::~ArrayList() {
  // deallocates array
  delete []array;
  array = nullptr;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList& rhs){
  length = rhs.length; // length of list is the same as length of rhs

  if(isEmpty() || length < 0)
  {
    array = nullptr;
  }
  else
  {
    array = new T[length]; // array has same length as list rhs

    for(std::size_t i = 0; i < length; i++)
    {
      array[i] = rhs.array[i]; // fills list with items in list rhs
    }
  }
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList rhs){
  ArrayList<T> tempList(rhs); // temporary list
  swap(tempList);
  return *this;
}

template <typename T>
void ArrayList<T>::swap(ArrayList& rhs) {
  std::swap(array, rhs.array);
  std::swap(length, rhs.length);
}

template <typename T>
bool ArrayList<T>::isEmpty() const noexcept {
  // an empty array has a size of 0
  if(length == 0)
  {
    return true;
  }

  return false;
}

template <typename T>
std::size_t ArrayList<T>::getLength() const noexcept {
  return length;
}

template <typename T>
bool ArrayList<T>::insert(std::size_t position, const T& item){

  // checks if position is valid
  if((position < 0) || (position > length))
  {
    return false;
  }
  else
  {
    // temporary array stores values of current array
    T *tempArray;
    tempArray = new T[length];
    for(std::size_t i = 0; i < length; i++)
    {
      tempArray[i] = array[i];
    }

    // deallocates current array
    delete []array;

    // resizes array
    length++;
    array = new T[length];

    // inserts new value
    // if inserting at the beginning of the array
    if(position == 0)
    {
      for(std::size_t i = 1; i < length; i++)
      {
        array[i] = tempArray[i - 1];
      }
      array[0] = item;
    }
    // if inserting at the end of the array
    else if(position == length)
    {
      for(std::size_t i = 0; i < length - 1; i++)
      {
        array[i] = tempArray[i];
      }
      array[position] = item;
    }
    // inserting at all other positions
    else
    {
      for(std::size_t i = 0; i < position; i++)
      {
        array[i] = tempArray[i];
      }
      for(std::size_t i = position + 1; i < length; i++)
      {
        array[i] = tempArray[i - 1];
      }
      array[position] = item;
    }

    return true;
  }
}
  

template <typename T>
bool ArrayList<T>::remove(std::size_t position){
  // checks if position is valid
  if((position < 0) || (position > length - 1) || (isEmpty()))
  {
    return false;
  }
  else
  {
    // temporary array stores values of current array
    T *tempArray;
    tempArray = new T[getLength()];
    for(std::size_t i = 0; i < getLength(); i++)
    {
      tempArray[i] = array[i];
    }

    // deallocates current array
    delete []array;

    // resizes array
    length--;
    array = new T[length];

    // removing value at position
    // if removing at the beginning of the array
    if(position == 0)
    {
      for(std::size_t i = 0; i < length; i++)
      {
        array[i] = tempArray[i + 1];
      }
    }
    // if removing at the end of the array
    else if(position == length)
    {
      for(std::size_t i = 0; i < length; i++)
      {
        array[i] = tempArray[i];
      }
    }
    // inserting at all other positions
    else
    {
      for(std::size_t i = 0; i < position; i++)
      {
        array[i] = tempArray[i];
      }
      for(std::size_t i = position; i < length; i++)
      {
        array[i] = tempArray[i + 1];
      }
    }

    return true;
  }
}

template <typename T>
void ArrayList<T>::clear() {
  // deallocates current array
  delete []array;

  // resizes array
  length = 0;
  array = new T[length];
}

template <typename T>
T ArrayList<T>::getEntry(std::size_t position) const {
  if((position < 0) || (position >= length) || (isEmpty()))
  {
    // returns nothing if position is invalid
    return T();
  }
  else
  {
    return array[position];
  }
}

template <typename T>
void ArrayList<T>::setEntry(std::size_t position, const T& newValue) {
  if((position < 0) || (position >= length))
  {
    // does nothing if position is invalid
    return;
  }
  else
  {
    array[position] = newValue;
  }
}
