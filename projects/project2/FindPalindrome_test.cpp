#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"
#include "FindPalindrome.hpp"

// There should be at least one test per FindPalindrome method

TEST_CASE( "Test adding a non-allowable word", "[FindPalindrome]" )
{
	FindPalindrome b;
	REQUIRE(!b.add("kayak1"));
}

TEST_CASE("test recursion", "[FindPalindrome]"){
	FindPalindrome b;

	REQUIRE(b.add("a"));
	REQUIRE(b.add("AA"));
	REQUIRE(b.add("AaA"));
	REQUIRE(b.number() == 6);
}

TEST_CASE( "[Test 1] constructor", "[FindPalindrome]" )
{
	FindPalindrome b;
	REQUIRE(b.number() == 0);
}

TEST_CASE( "[Test 2] number", "[FindPalindrome]" )
{
	FindPalindrome b;
	b.add("a");
	REQUIRE(b.number() == 1);
}

TEST_CASE( "[Test 3] clear", "[FindPalindrome]" )
{
	FindPalindrome b;
	b.add("a");
	b.add("b");
	b.clear();
	REQUIRE(b.number() == 0);
}

TEST_CASE( "[Test 4] cutTest1", "[FindPalindrome]" )
{
	FindPalindrome b;
	std::vector<std::string> check;
	check.push_back("aha");
	REQUIRE(b.cutTest1(check) == true);
}

TEST_CASE( "[Test 5] cutTest2", "[FindPalindrome]" )
{
	FindPalindrome b;
	std::vector<std::string> check, check2;
	check.push_back("aha");
	check2.push_back("a");
	REQUIRE(b.cutTest2(check, check2) == true);
}

TEST_CASE( "[Test 6] add", "[FindPalindrome]" )
{
	FindPalindrome b;
	b.add("v");
	REQUIRE(b.add("a"));
}

TEST_CASE( "[Test 7] addv2", "[FindPalindrome]" )
{
	FindPalindrome b;
	b.add("v");
	std::vector<std::string> check;
	REQUIRE(b.add("a"));
}
