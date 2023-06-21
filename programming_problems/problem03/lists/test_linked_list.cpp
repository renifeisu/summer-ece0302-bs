#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.hpp"

template class LinkedList<int>;

TEST_CASE( "TODO", "[LinkedList]" ) {

    LinkedList<int> list;
}

TEST_CASE( "[Test 1] Default Constructor", "[LinkedList]" ) {

  LinkedList<int> list;
  REQUIRE(list.isEmpty());
}

TEST_CASE( "[Test 2] Copy Constructor", "[LinkedList]" ) {

  LinkedList<int> list;
  list.insert(0, 1);
  list.insert(0, 2);
  LinkedList<int> copyList(list);

  REQUIRE(copyList.getLength() == 2);
}

TEST_CASE( "[Test 3] Copy Operator", "[LinkedList]" ) {

  LinkedList<int> list, copyList;
  list.insert(0, 1);
  list.insert(0, 2);
  copyList = list;

  REQUIRE(copyList.getLength() == 2);
  REQUIRE(copyList.getEntry(1) == 1);
  REQUIRE(copyList.getEntry(0) == 2);
}

TEST_CASE( "[Test 4] Swap", "[LinkedList]" ) {

  LinkedList<int> list, copyList;
  list.insert(0, 1);
  list.insert(0, 2);
  list.swap(copyList);

  REQUIRE(copyList.getLength() == 2);
  REQUIRE(list.isEmpty());
  REQUIRE(copyList.getEntry(1) == 1);
  REQUIRE(copyList.getEntry(0) == 2);
}


TEST_CASE( "[Test 5] isEmpty", "[LinkedList]" ) {

  LinkedList<int> list, list1;
  list1.insert(0, 1);

  REQUIRE(list.isEmpty());
  REQUIRE(list1.isEmpty() == false);
}

TEST_CASE( "[Test 6] getLength", "[LinkedList]" ) {

  LinkedList<int> list, list1;
  list1.insert(0, 1);

  REQUIRE(list.getLength() == 0);
  REQUIRE(list1.getLength() == 1);
}

TEST_CASE( "[Test 7] insert", "[LinkedList]" ) {

  LinkedList<int> list;

  REQUIRE(list.insert(0, 1));
  REQUIRE(list.insert(3,1) == false);
  REQUIRE(list.getEntry(0) == 1);
}

TEST_CASE( "[Test 8] remove", "[LinkedList]" ) {

  LinkedList<int> list, list1;
  list1.insert(0,3);

  REQUIRE(list.remove(0) == false);
  REQUIRE(list1.remove(0));
}

TEST_CASE( "[Test 9] clear", "[LinkedList]" ) {

  LinkedList<int> list;
  list.insert(0, 1);
  list.clear();
  REQUIRE(list.isEmpty());
}

TEST_CASE( "[Test 10] getEntry", "[LinkedList]" ) {

  LinkedList<int> list;
  list.insert(0, 2);
  REQUIRE(list.getEntry(0) == 2);
}

TEST_CASE( "[Test 11] setEntry", "[LinkedList]" ) {

  LinkedList<int> list;
  list.insert(0, 1);
  list.setEntry(0, 3);
  REQUIRE(list.getEntry(0) == 3);
}

TEST_CASE( "[Test 12] testing", "[LinkedList]" ) {

    LinkedList<int> list;

    list.insert(0,0);
    list.insert(1,1);
    list.insert(2,2);
    list.insert(3,3);
    list.insert(4,4);

    list.remove(2); // remove middle element
    list.remove(0); // remove first element
    list.remove(2); // remove end element

    REQUIRE(list.getLength() == 2);

  }

