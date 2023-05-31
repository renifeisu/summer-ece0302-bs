#ifndef _ABSTRACT_BAG_HPP_
#define _ABSTRACT_BAG_HPP_

#include <cstdlib>

/**
 * Abstract Bag is an interface that allows future classes to be derived from it.
 * It gives a basic structure for other classes relating to bags.
 * This class only contains pure virtual functions.
 * 
 * @author Beryl Sin
 * @version 1.0
 * @since 2023-05-25
*/
template<typename T> class AbstractBag{
public:
  
  /**
   * Default constructor; Presets certain conditions for this bag
   * 
   * @post Deletes object
  */
  virtual ~AbstractBag() {};

  /**
   * Gets the current size of this bag
   * 
   * @pre Bag must be valid
   * @return Returns a data type of size_t, representing the current size of the bag
  */
  virtual std::size_t getCurrentSize() const = 0;

  /**
   * Checks if this bag is empty or not
   * 
   * @pre Bag must be valid
   * @return Returns a data type of bool, TRUE if bag is empty, FALSE if bag is not empty
  */
  virtual bool isEmpty() const = 0;

  /**
   * Adds an item to this bag
   * 
   * @param entry Represents an item to be put into this bag
   * @pre If there is a max size for this bag, and the current size of this bag is >=
   * to the max size, an item cannot be added to this bag
   * @post If an item is successfully added, the item will be added to the end of this bag and 
   * the size of this bag increases by one
   * @return Returns a data type of bool, TRUE if item was added, FALSE if item cannot be added
  */
  virtual bool add(const T& entry) = 0;

  /**
   * Removes an item from this bag
   * 
   * @param entry Represents an item to be removed from this bag
   * @pre If this bag is empty, an item cannot be removed
   * @post If an item is successfully removed, the size of this bag will decrease by one
   * @post Depending on the item's index: if the item's index is equal to the size of this bag - 1, 
   * nothing occupies the item's position; otherwise, the other items after the removed item will be shifted
   * so that the next item occupies the removed item's position and so forth
   * @return Returns a data type of bool, TRUE if item was removed, FALSE if item cannot be removed
  */
  virtual bool remove(const T& entry) = 0;

  /**
   * Clears this bag
   * 
   * @post The size of this bag will become 0
  */
  virtual void clear() = 0;

  /**
   * Counts the number of times an entry appears in this bag
   * 
   * @param entry Represents the item that gets checked for the amount of times it will appear
   * @pre Bag must be valid
   * @return Returns a data type of size_t, represents the amount of times the item appears in this bag
  */
  virtual std::size_t getFrequencyOf(const T& entry) const = 0;

  /**
   * Checks to see if an entry exists in this bag
   * 
   * @param entry Represents the item that gets checked if it exists in this bag
   * @pre Bag must be valid
   * @return Returns a data type of bool, TRUE if the entry occurs at least once, FALSE if the entry does not occur
  */
  virtual bool contains(const T& entry) const = 0;

};

#endif