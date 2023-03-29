

/**
 * This file contains some simple tests.
 *
 * DO NOT add the #define CATCH_CONFIG_RUNNER to this file.
 * It is already in catch_setup.cpp
 *
 * Note that you can have more than one cpp file with tests in them.
 * For example, you could have a test file for your DSString and a
 * separate one for your DSVector.
 */

#include "catch.hpp"
#include "AVLTree.h"
#include <map>


TEST_CASE("AVL Tree", "[AVL]") {
    AVLTree<string, string> amp;
    char *a[3] = {"a", "b", "c"};

    amp.insertGetV(a[0], "doc");
    amp.insertGetV(a[1])="2";


    SECTION("INSERT") {
        CHECK(amp.insertGetV("a") == "doc");
    }
    SECTION("FIND"){
        CHECK(amp.find("a")=="doc");
        CHECK(amp.find("b")=="2");
    }

}