#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h>
#include <stdlib.h>
#include <string>

class Bitset{
public:

  // default construction of a valid bitset of size 8, with all bits set to 0.
  Bitset();

  // construction of a valid bitset of size N, where N is of type intmax_t with all 
  // bits set to 0.
  // the bitset is invalid if N <= 0.
  Bitset(intmax_t size);

  // construction of a valid bitset initialized with a string of the form 00010000.
  // If the string contains any character other than 0 or 1, the bitset is invalid.
  // The string can be any length and the size of the bitset should be allocated
  // according to the length of the string
  Bitset(const std::string & value);

  // destructor that deletes the bitset array
  ~Bitset();

  Bitset(const Bitset & ) = delete;
  Bitset & operator=(const Bitset &) = delete;

  // a method to return the size of the bitset.
  intmax_t size() const;

  // a method to determine if the bitset is valid.
  bool good() const;

  // a method to set the nth bit to 1, and if n is not in [0, N-1] then the bitset 
  // becomes invalid. 
  // Assume that index 0 is the leftmost bit and index n is the rightmost bit.
  void set(intmax_t index);

  // a method to reset the nth bit to 0, and if n is not in [0, N-1] then the bitset 
  // becomes invalid.
  void reset(intmax_t index);

  // a method to toggle the nth bit (1 to 0 or 0 to 1), and if n not in [0, N-1] then 
  // the bitset becomes invalid
  void toggle(intmax_t index);

  // a method to check if the nth bit is set (1) by returning a bool value of true if 
  // set and false if not, and if n is not in [0, N-1] then the bitset becomes invalid 
  // and false is returned.
  bool test(intmax_t index);

  // a method to return the bitset as a std::string of characters 0 and 1.
  // This string should represent the bitset digits from left-to-right with the most 
  // significant bit first.
  std::string asString() const;

private:

  // variable representing bitset
  intmax_t *bitset;
   
  // variable representing bitset size
  intmax_t bitset_size;

  // variable representing validity
  bool valid = true;

};

#endif
