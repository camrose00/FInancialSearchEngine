//
// Created by Cameron Rosenberger on 6/22/22.
//
#define DEBUG  false

#include "DocumentParser.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "porter2_stemmer/porter2_stemmer.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>


using namespace rapidjson;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::setw;
using std::left;


DocumentParser::DocumentParser(){

}
void DocumentParser::makeStops() {
    makePunct();
    ifstream sc("../Data/stopWords.txt");
    if (!sc.is_open()) {
        throw runtime_error("Stopwords file not open");
    }
    string input;
    while (sc >> input) {
        stops.insert(input);
    }
    sc.close();
}

void DocumentParser::punctDestroyer(string &arg) {
   for(int i=0,len=arg.size();i<len;i++){
       if(!ispunct(arg[i])){
           arg[i]=tolower(arg[i]);
       }else{
          arg.erase(i--,1);
          len = arg.size();
       }
   }

}
void DocumentParser::tokenize(std::string &arg, int & fileNum) {
    char *token;
    char* temp = arg.data();
    token = strtok( temp, " ");

    while (token != nullptr) {
        string intermediate(token);
        punctDestroyer(intermediate);
        Porter2Stemmer::stem(intermediate);

        if (stops.find(intermediate) == stops.end()) {
            if (DEBUG)
                cout << intermediate << endl;

        texts.insertGetV(intermediate)[fileNum]++;
        }
        token = strtok(nullptr, " ");
    }
}
void DocumentParser::testReadJsonFile(const char *fileName,int fileNum) {
    if (DEBUG)
        cout << "TEST FILE P:" << fileName << endl;

    ifstream input(fileName);
    if (!input.is_open())
        std::cerr << "cannot open file" << endl;
    IStreamWrapper isw(input);
    Document d;
    d.ParseStream(isw);

    auto entities = d["entities"]["organizations"].GetArray();
    for(auto& e: entities){
        if(DEBUG){
        cout<<"FILENAME:"<<fileName<<endl;
        cout<<"ORGS: "<<e["name"].GetString()<<endl;
        }
        string org = e["name"].GetString();
        punctDestroyer(org);
        Porter2Stemmer::stem(org);
        orgs.insertGetV(org)[fileNum]++;
    }
    auto persons = d["entities"]["persons"].GetArray();
    if(DEBUG)
    cout << "  Person Entities:" << endl;
    for (auto &p: persons) {
        if(DEBUG) {
            cout << "    > " << setw(30) << left << p["name"].GetString()
                 << setw(10) << left << p["sentiment"].GetString() << endl;
        }
        string person = p["name"].GetString();
        punctDestroyer(person);
        Porter2Stemmer::stem(person);
        people.insertGetV(person)[fileNum]++;
    }

    string&& text = d["text"].GetString();
    tokenize(text, fileNum);

    input.close();
}

void DocumentParser::testFileSystem(const char *path) {
    auto it = std::filesystem::recursive_directory_iterator(path);
    int i = 1;
    //loop over all the entries.
    for (const auto &entry: it) {
        if (DEBUG) {
            cout << "PATH--- " << setw(60) << left << entry.path().c_str() << " ---" << endl;
        }
        //We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            testReadJsonFile(entry.path().c_str(),i);
            files.insert({i,entry.path()});
            if (i % 1000==0) {
                cout << i << endl;
                //cout<<entry.path()<<endl;
            }
            i++;
        }
    }
}
void DocumentParser::makePunct() {
    ifstream sc("../Data/punct.txt");
    if(!sc.is_open()){
        throw runtime_error("Punct error");
    }
    char next;
    while(sc>>next){
        punctuation.insert(next);
    }
    sc.close();
}


AVLTree<string, unordered_map<int,int>> &DocumentParser::getText() {
    return texts;
}

AVLTree<string, unordered_map<int,int>> &DocumentParser::getPeople() {
    return people;
}

AVLTree<string, unordered_map<int,int>> &DocumentParser::getOrgs() {
    return orgs;
}

unordered_set<string>& DocumentParser::getStops(){
    return stops;
}
unordered_set<char>& DocumentParser::getPunct(){
    return punctuation;
}
unordered_map<int,string>& DocumentParser::getFiles(){
    return files;
}