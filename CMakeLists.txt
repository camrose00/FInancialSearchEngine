cmake_minimum_required(VERSION 3.14)
project(22su_search_engine)

set(CMAKE_CXX_STANDARD 17)

# The configure_file statements below ensure that files are copied into the data
# folder that will be created in the build folder.
file(COPY sample_data/ DESTINATION sample_data/)


# This target is for the main project.
add_executable(22su_search_engine main.cpp BinarySearchTree.h DocumentParser.cpp DocumentParser.h porter2_stemmer/util/hash.h porter2_stemmer/util/string_view.h porter2_stemmer/porter2_stemmer.cpp porter2_stemmer/porter2_stemmer.h Query.cpp Query.h UI.cpp UI.h)

# this is the testing target.  Don't include your main driver.cpp file in this target.
add_executable(22su_search_engine_tests catch.hpp catch_setup.cpp DataStructure_Tests.cpp catch_setup.h  AVLIntTree.cpp AVLIntTree.h AVLTree.h Query.cpp Query.h)