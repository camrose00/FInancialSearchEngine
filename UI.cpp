//
// Created by Cameron Rosenberger on 6/28/22.
//

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
#include "UI.h"
#include "Query.h"

using namespace std;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::setw;
using std::left;

UI::UI() {

}

void UI::welcome(const char *file) {
    DocumentParser dp;
    Query q;
    bool cntrl = true;
    while (cntrl) {
        cout << "--------------------------------------------" << endl;
        cout << setw(25) << right << "Welcome" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "C - Clear Index" << endl;
        cout << "P - Parse Dataset" << endl;
        cout << "S - Search" << endl;
        cout << "Q - Quit" << endl;
        string first;
        cin >> first;
        if (first == "C") {
            q.files.clear();
            q.people.destroy();
            q.orgs.destroy();
            q.texts.destroy();
            cout << "Index Cleared" << endl;
        } else if (first == "P") {
            dp.testFileSystem(file);
            files = dp.getFiles();

            q.files = dp.getFiles();
            q.people = dp.getPeople();
            q.texts = dp.getText();
            q.orgs = dp.getOrgs();
            q.punctuation = dp.getPunct();
        } else if (first == "S") {

            if(q.files.empty()){
                cout<<"Parse dataset first"<<endl;
                continue;
            }
            string search;

            unordered_map<int, int> key;

            cout << "   Search: ";
            cin.ignore();
           getline(cin,search);
            if (search == "Q") {
                break;
            }
            key = q.getInputLocations(search);
            if (key.empty()) {
                cout << "\tSearch not found." << endl;

                continue;
            }


            cout << endl;
            bool rep = true;
            vector<string> files = displayResults(key);
            while (rep) {

                string request;
                rep = false;
                cout<<endl;
                cout << "Enter a letter for a file or '-1' to return: ";

                cin>>request;

                if (request == "Q") {
                    cntrl = false;
                    break;
                } else if (request == "N") {
                    cout << "   Search: ";

                } else if(request == "-1"){
                   break;
                }else{
                    try{
                        int num = getI(request);
                        showFullFile(files[num]);

                    } catch (exception) {
                        cout << "Unknown Input" << endl;
                        rep = true;
                    }
                }
            }
        }else if(first == "Q"){
            exit(1);
        }else{
            cout<<"Invalid Input"<<endl;
        }
    }
}

int UI::getI(string arg) {
    for (int i = 0; i < 15; i++) {
        if (arg == tabs[i]) {
            return i;
        }
    }
    throw runtime_error("Get I out of bounds");
}

vector<pair<int, int>> UI::sort(unordered_map<int, int> &arg) {
    vector<pair<int, int>> temp;

    for (auto &it: arg) {
        temp.emplace_back(it);
    }

    for (int j = 0; j < temp.size(); j++) {
        int max = j;
        for (int i = j; i < temp.size(); i++) {
            if (temp[i].second > temp[max].second) {
                swap(temp[i], temp[max]);
            }
        }
    }
    return temp;
}

void UI::showFullFile(string &fileName) {
    ifstream input(fileName);
    if (!input.is_open())
        throw runtime_error("Show Full File Error");
    rapidjson::IStreamWrapper isw(input);
    rapidjson::Document d;
    d.ParseStream(isw);

    cout << endl;
    // cout<<"----------"<<d["thread"]["section_title"].GetString()<<"----------"<<endl;
    cout << "\tTitle: " << d["title"].GetString() << endl;
    cout<<"\tAuthor: "<<d["author"].GetString()<<endl;
    cout << endl;
    cout << "\t\t" << d["text"].GetString() << endl;
    cout << endl;
    input.close();
}

string UI::fileCounter(int count) {
    auto it = files.find(count);
    if (it != files.end()) {
        return it->second;
    }
    throw runtime_error("File counter not found");
}

string UI::showTitle(string &fileName) {
    ifstream input(fileName);
    if (!input.is_open())
        std::cerr << "cannot open file" << endl;
    rapidjson::IStreamWrapper isw(input);
    rapidjson::Document d;
    d.ParseStream(isw);

    return d["title"].GetString();
}

vector<string> UI::displayResults(unordered_map<int, int> &arg) {
    vector<pair<int, int>> temp = sort(arg);
    vector<string> fileStrings;
    int i = 0;
    auto ip = temp.begin();
    while (ip != temp.end() && i < 15) {
        string fileName = fileCounter(ip->first);
        cout << "\t" << tabs[i] << " - " << showTitle(fileName) << endl;
        fileStrings.push_back(fileName);
        i++;
        ip++;
    }
    return fileStrings;
}

