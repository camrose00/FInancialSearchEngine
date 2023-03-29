//
// Created by Cameron Rosenberger on 6/22/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_DOCUMENTPARSER_H
#define INC_22SU_SEARCH_ENGINE_DOCUMENTPARSER_H

#include <string>
#include <unordered_set>
#include "AVLTree.h"
#include <map>
#include <unordered_map>
#include <set>
using namespace std;

class DocumentParser {
public:
    DocumentParser();
    unordered_set<char> punctuation;
    unordered_set<string> stops;
    AVLTree<string,unordered_map<int,int>> people;
    AVLTree<string,unordered_map<int,int>> orgs;
    AVLTree<string,unordered_map<int,int>> texts;
    unordered_map<int,string> files;

    AVLTree<string,unordered_map<int,int>>& getPeople();
    AVLTree<string,unordered_map<int,int>>& getOrgs();
    AVLTree<string,unordered_map<int,int>>& getText();
    unordered_set<string>& getStops();
    unordered_set<char>& getPunct();

    void testFileSystem(const char*);
    void testReadJsonFile(const char*,int);

    void tokenize(string&,int&);
    void punctDestroyer(string &);

    void getElement(string&);

    void makeStops();
    void makePunct();

    string fileCounter(int);

    vector<int> getRelevancy( int, string&,string&);

    unordered_map<int, string> &getFiles();
};


#endif //INC_22SU_SEARCH_ENGINE_DOCUMENTPARSER_H
