#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "array_list.hpp"

//force class expansion
template class ArrayList<int>;

TEST_CASE( "Test", "[ArrayList]" ) {

  ArrayList<int> list;
}

TEST_CASE( "[Test 1] Default Constructor", "[ArrayList]" ) {

  ArrayList<int> list;
  REQUIRE(list.isEmpty());
}

TEST_CASE( "[Test 2] Copy Constructor", "[ArrayList]" ) {

  ArrayList<int> list;
  list.insert(0, 1);
  list.insert(0, 2);
  ArrayList<int> copyList(list);

  REQUIRE(copyList.getLength() == 2);
  REQUIRE(copyList.getEntry(0) == 2);
  REQUIRE(copyList.getEntry(1) == 1);
}

TEST_CASE( "[Test 3] Copy Operator", "[ArrayList]" ) {

  ArrayList<int> list, copyList;
  list.insert(0, 1);
  list.insert(0, 2);
  copyList = list;

  REQUIRE(copyList.getLength() == 2);
  REQUIRE(copyList.getEntry(0) == 2);
  REQUIRE(copyList.getEntry(1) == 1);
}

TEST_CASE( "[Test 4] Swap", "[ArrayList]" ) {

  ArrayList<int> list, copyList;
  list.insert(0, 1);
  list.insert(0, 2);
  list.swap(copyList);

  REQUIRE(copyList.getLength() == 2);
  REQUIRE(copyList.getEntry(0) == 2);
  REQUIRE(copyList.getEntry(1) == 1);
  REQUIRE(list.isEmpty());
}

TEST_CASE( "[Test 5] isEmpty", "[ArrayList]" ) {

  ArrayList<int> list, list1;
  list1.insert(0, 1);

  REQUIRE(list.isEmpty());
  REQUIRE(list1.isEmpty() == false);
}

TEST_CASE( "[Test 6] getLength", "[ArrayList]" ) {

  ArrayList<int> list, list1;
  list1.insert(0, 1);

  REQUIRE(list.getLength() == 0);
  REQUIRE(list1.getLength() == 1);
}

TEST_CASE( "[Test 7] insert", "[ArrayList]" ) {

  ArrayList<int> list;

  REQUIRE(list.insert(0, 1));
  REQUIRE(list.insert(3,1) == false);
  REQUIRE(list.getEntry(0) == 1);
}

TEST_CASE( "[Test 8] remove", "[ArrayList]" ) {

  ArrayList<int> list, list1;
  list1.insert(0,3);

  REQUIRE(list.remove(0) == false);
  REQUIRE(list1.remove(0));
}

TEST_CASE( "[Test 9] clear", "[ArrayList]" ) {

  ArrayList<int> list;
  list.insert(0, 1);
  list.clear();
  REQUIRE(list.isEmpty());
}

TEST_CASE( "[Test 10] getEntry", "[ArrayList]" ) {

  ArrayList<int> list;
  list.insert(0, 2);
  REQUIRE(list.getEntry(0) == 2);
}

TEST_CASE( "[Test 11] setEntry", "[ArrayList]" ) {

  ArrayList<int> list;
  list.insert(0, 1);
  list.setEntry(0, 3);
  REQUIRE(list.getEntry(0) == 3);
}