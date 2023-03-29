//
// Created by Justin Chow on 6/27/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_QUERY_H
#define INC_22SU_SEARCH_ENGINE_QUERY_H

#include <string>
#include <vector>
#include <unordered_set>
#include "AVLTree.h"
#include <map>
#include <unordered_map>

using namespace std;

class Query {
public:

    unordered_set<string> stops;
    unordered_set<char> punctuation;
    AVLTree<string, unordered_map<int, int>> people;
    AVLTree<string, unordered_map<int, int>> orgs;
    AVLTree<string, unordered_map<int, int>> texts;
    unordered_map<int, string> files;

    Query();

    void punctDestroyer(string&);

    unordered_map<int, int> getInputLocations(string );

    void getInfo();

};


#endif //INC_22SU_SEARCH_ENGINE_QUERY_H
