#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "limited_size_bag.hpp"

// force template expansion for ints
template class LimitedSizeBag<int>;

TEST_CASE("Calling all public members", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;

  b.add(0);
  b.remove(0);
  b.isEmpty();
  b.getCurrentSize();
  b.clear();
  b.getFrequencyOf(0);
  b.contains(0);

}

TEST_CASE("[Test 1] Default Constructor", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;

  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());
}

TEST_CASE("[Test 2] add", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  b.add(1);

  REQUIRE(b.getCurrentSize() == 1);
  REQUIRE(b.isEmpty() == false);
  REQUIRE(b.contains(1));
}

TEST_CASE("[Test 3] remove", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  b.add(1);
  b.add(2);
  b.remove(1);

  LimitedSizeBag<int> b2;

  REQUIRE(b.remove(2) == true);
  REQUIRE(b.getCurrentSize() == 1);
  REQUIRE(b.isEmpty() == false);
  REQUIRE(b.contains(2));
  REQUIRE(b2.remove(1) == false);
}

TEST_CASE("[Test 4] isEmpty", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;

  LimitedSizeBag<int> b2;
  b2.add(1);

  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty() == true);
  REQUIRE(b2.isEmpty() == false);

}

TEST_CASE("[Test 5] getCurrentSize", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;

  LimitedSizeBag<int> b2;
  b2.add(1);

  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());
  REQUIRE(b2.getCurrentSize() == 1);
}

TEST_CASE("[Test 6] clear", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  b.add(1);
  b.add(2);
  b.clear();

  REQUIRE(b.getCurrentSize() == 0);
  REQUIRE(b.isEmpty());
}

TEST_CASE("[Test 7] getFrequencyOf", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  b.add(1);
  b.add(2);
  b.add(1);

  REQUIRE(b.getCurrentSize() == 3);
  REQUIRE(b.isEmpty() == false);
  REQUIRE(b.getFrequencyOf(1) == 2);
}

TEST_CASE("[Test 8] contains", "[LimitedSizeBag]"){
  LimitedSizeBag<int> b;
  b.add(1);

  REQUIRE(b.getCurrentSize() == 1);
  REQUIRE(b.isEmpty() == false);
  REQUIRE(b.contains(1));
  REQUIRE(b.contains(0) == false);
}

TEST_CASE("[Test 9] maxsize", "[LimitedSizeBag]"){
  int x = LimitedSizeBag<int>::maxsize;
  LimitedSizeBag<int> b;
  for(int i = 0; i < 200; i++)
  {
    b.add(1);
  }

  LimitedSizeBag<int> b2;

  REQUIRE(b.getCurrentSize() > x);
  REQUIRE(b2.getCurrentSize() < x );
}
