#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include <iostream>
#include "bitset.hpp"

TEST_CASE( "Test bitset default construction", "[bitset]" ) {

    Bitset b;  
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
}

TEST_CASE( "Test bitset construction with asString", "[bitset]" ) {
    Bitset b;
    REQUIRE(b.asString().compare("00000000") == 0);
}

TEST_CASE( "Test bitset construction size", "[bitset]" ) {
    Bitset b(64);
    std::string s(64, '0');
    REQUIRE(b.size() == 64);
    REQUIRE(b.good());
}

TEST_CASE( "Test bitset construction string", "[bitset]" ) {
    std::string s("00101110000011000001101000001");
    Bitset b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test bitset construction invalid string", "[bitset]" ) {
    std::string s("00101110000011002001101000001");
    Bitset b(s);
    REQUIRE_FALSE(b.good());
}

TEST_CASE( "Test set", "[bitset]" ) {
    std::string s("00010001");
    Bitset b;
    b.set(3);
    b.set(7);
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test set with default init", "[bitset]" ) {
    std::string s("00010001");
    Bitset b;
    b.set(3);
    b.set(7);
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test set with size init", "[bitset]" ) {
    std::string s("00010");
    Bitset b(5);
    b.set(3);
    REQUIRE(b.size() == 5);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "Test combined", "[bitset]" ) {
    std::string s((1<<15) + 3, '0');
    Bitset b(s);
    REQUIRE(b.size() == s.size());
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);

    for (int i = 1; i < (1<<10); i++) {
        b.set(i);
        b.reset(i + (1<<10));
        b.toggle(i + (1<<11));
        REQUIRE(b.good());
        REQUIRE(b.test(i));
        REQUIRE_FALSE(b.test(i + (1<<10)));
        REQUIRE(((b.test(i + (1<<11)) == true && s.at(i + (1<<11)) == '0') || (b.test(i + (1<<11)) == false && s.at(i + (1<<11)) == '1')));
    }
}

TEST_CASE( "[Test 1] Default Construction", "[bitset]" ) {
    std::string s = "00000000";
    Bitset b;
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "[Test 2] Bitset of Size N", "[bitset]" ) {
    std::string s = "0";
    Bitset b(1);
    REQUIRE(b.size() == 1);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "[Test 3] Bitset of Size N - Invalid", "[bitset]" ) {
    Bitset b(0);
    REQUIRE(b.good() == 0);
}

TEST_CASE( "[Test 4] Bitset of String", "[bitset]" ) {
    std::string s = "00010000";
    Bitset b("00010000");
    REQUIRE(b.size() == 8);
    REQUIRE(b.good());
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "[Test 5] Bitset of String - Invalid", "[bitset]" ) {
    Bitset b("00020000");
    REQUIRE(b.size() == 8);
    REQUIRE(b.good() == 0);
}

TEST_CASE( "[Test 6] Size", "[bitset]" ) {
    Bitset b(100);
    REQUIRE(b.size() == 100);
}

TEST_CASE( "[Test 7] Validity", "[bitset]" ) {
    Bitset b(0);
    REQUIRE(b.good() == 0);
}

TEST_CASE( "[Test 8] Set", "[bitset]" ) {
    std::string s = "0010";
    Bitset b("0000");
    b.set(2);
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "[Test 9] Set - Invalid", "[bitset]" ) {
    Bitset b("0000");
    b.set(5);
    REQUIRE(b.good() == 0);
}

TEST_CASE( "[Test 10] Reset", "[bitset]" ) {
    std::string s = "0";
    Bitset b("1");
    b.reset(0);
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "[Test 11] Reset - Invalid", "[bitset]" ) {
    Bitset b("1");
    b.reset(2);
    REQUIRE(b.good() == 0);
}

TEST_CASE( "[Test 12] Toggle", "[bitset]" ) {
    std::string s = "1";
    Bitset b(1);
    b.toggle(0);
    REQUIRE(b.asString().compare(s) == 0);
}

TEST_CASE( "[Test 13] Toggle - Invalid", "[bitset]" ) {
    Bitset b(1);
    b.toggle(2);
    REQUIRE(b.good() == 0);
}

TEST_CASE( "[Test 14]  - Test 1", "[bitset]" ) {
    Bitset b("1");
    REQUIRE(b.test(0) == 1);
}

TEST_CASE( "[Test 15]  - Test 2", "[bitset]" ) {
    Bitset b(1);
    REQUIRE(b.test(0) == 0);
}

TEST_CASE( "[Test 16]  - Test - Invalid", "[bitset]" ) {
    Bitset b(1);
    REQUIRE(b.test(2) == 0);
}

TEST_CASE( "[Test 17]  - asString", "[bitset]" ) {
    std::string s = "0101010101";
    Bitset b("0101010101");
    REQUIRE(b.asString().compare(s) == 0);
}