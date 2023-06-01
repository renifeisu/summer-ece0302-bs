#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "dynamic_bag.hpp"

// force template expansion for ints
template class DynamicBag<int>;

TEST_CASE("Calling all public members", "[DynamicBag]"){
  DynamicBag<int> b;
  int a = 1;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);
}

TEST_CASE("[Test 1] Default Constructor", "[DynamicBag]"){
  DynamicBag<int> b;

  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());
}

TEST_CASE("[Test 2] Copy Constructor", "[DynamicBag]"){
  DynamicBag<int> b1;
  b1.add(1);
  b1.add(2);
  DynamicBag<int> b2(b1);

  REQUIRE(b2.getCurrentSize() == 2);
  REQUIRE(b2.contains(1));
  REQUIRE(b2.contains(2));
}

TEST_CASE("[Test 3] Copy Assignment", "[DynamicBag]"){
  DynamicBag<int> b1;
  b1.add(1);
  b1.add(2);
  DynamicBag<int> b2;
  b2 = b1;

  REQUIRE(b2.getCurrentSize() == 2);
  REQUIRE(b2.contains(1));
  REQUIRE(b2.contains(2));
}

TEST_CASE("[Test 4] Swap", "[DynamicBag]"){
  DynamicBag<int> b1;
  b1.add(1);
  b1.add(2);
  DynamicBag<int> b2;
  b2.swap(b1);

  REQUIRE(b2.getCurrentSize() == 2);
  REQUIRE(b2.contains(1));
  REQUIRE(b2.contains(2));
  REQUIRE(b1.isEmpty());
}

TEST_CASE("[Test 5] Add", "[DynamicBag]"){
  DynamicBag<int> b;
  b.add(1);
  
  REQUIRE(b.contains(1));
}

TEST_CASE("[Test 6] Remove", "[DynamicBag]"){
  DynamicBag<int> b;
  b.add(1);
  DynamicBag<int> b2;

  REQUIRE(b.remove(1));
  REQUIRE(b2.remove(2) == false);
}

TEST_CASE("[Test 7] isEmpty", "[DynamicBag]"){
  DynamicBag<int> b;

  REQUIRE(b.isEmpty());
}

TEST_CASE("[Test 8] getCurrent Size", "[DynamicBag]"){
  DynamicBag<int> b;

  REQUIRE(b.getCurrentSize() == 0);
}

TEST_CASE("[Test 9] clear", "[DynamicBag]"){
  DynamicBag<int> b1;
  b1.add(1);
  b1.add(2);
  b1.clear();

  REQUIRE(b1.isEmpty());
}

TEST_CASE("[Test 10] getFrequencyOf", "[DynamicBag]"){
  DynamicBag<int> b1;
  b1.add(1);

  REQUIRE(b1.getFrequencyOf(1) == 1);
}

TEST_CASE("[Test 11] contains", "[DynamicBag]"){
  DynamicBag<int> b1;
  b1.add(2);

  REQUIRE(b1.contains(1) == false);
  REQUIRE(b1.contains(2) == true);
}



