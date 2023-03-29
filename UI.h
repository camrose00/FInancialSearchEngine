//
// Created by Cameron Rosenberger on 6/28/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_UI_H
#define INC_22SU_SEARCH_ENGINE_UI_H

#include <string>
#include <unordered_map>
using namespace std;

class UI {
public:
    string tabs[15] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O"};
    unordered_map<int,string> files;
    UI();
    void welcome(const char*);
    void getInfo();
    bool cmp(pair<int,int>&,pair<int,int>&);


    vector<pair<int,int>> sort(unordered_map<int, int> &arg);

    string fileCounter(int count);

    vector<string> displayResults(unordered_map<int, int> &arg);
    string showTitle(string&);
    void showFullFile(string &fileName);

    int getI(string arg);
};


#endif //INC_22SU_SEARCH_ENGINE_UI_H
