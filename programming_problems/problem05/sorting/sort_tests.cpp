#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"
#include "sort.hpp"

// write your test cases here
TEST_CASE("Test case", "sorting"){

  LinkedList<int> lst;

  lst.insert(0, 100);
  lst.insert(1, 4);
  lst.insert(2, 10);
  lst.insert(3, 25);
  lst.insert(4, 11);

  LinkedList<int> sorted = sort(lst);

  // check sorted list
  REQUIRE(sorted.getEntry(0) == 4);
  REQUIRE(sorted.getEntry(1) == 10);
  REQUIRE(sorted.getEntry(2) == 11);
  REQUIRE(sorted.getEntry(3) == 25);
  REQUIRE(sorted.getEntry(4) == 100);
  
}

TEST_CASE("[TEST 1] Char", "sorting"){

  LinkedList<char> lst;

  lst.insert(0, 'b');
  lst.insert(1, 'e');
  lst.insert(2, 'r');
  lst.insert(3, 'y');
  lst.insert(4, 'l');

  LinkedList<char> sorted = sort(lst);

  // check sorted list
  REQUIRE(sorted.getEntry(0) == 'b');
  REQUIRE(sorted.getEntry(1) == 'e');
  REQUIRE(sorted.getEntry(2) == 'l');
  REQUIRE(sorted.getEntry(3) == 'r');
  REQUIRE(sorted.getEntry(4) == 'y');
  
}

TEST_CASE("[TEST 2] Length", "sorting"){

  LinkedList<char> lst;

  lst.insert(0, 'b');
  lst.insert(1, 'e');
  lst.insert(2, 'r');
  lst.insert(3, 'y');
  lst.insert(4, 'l');
  lst.insert(5, 's');
  lst.insert(5, 'i');
  lst.insert(5, 'n');
  


  LinkedList<char> sorted = sort(lst);

  // check sorted list
  REQUIRE(sorted.getEntry(0) == 'b');
  REQUIRE(sorted.getEntry(1) == 'e');
  REQUIRE(sorted.getEntry(2) == 'i');
  REQUIRE(sorted.getEntry(3) == 'l');
  REQUIRE(sorted.getEntry(4) == 'n');
  REQUIRE(sorted.getEntry(5) == 'r');
  REQUIRE(sorted.getEntry(6) == 's');
  REQUIRE(sorted.getEntry(7) == 'y');
  
}

