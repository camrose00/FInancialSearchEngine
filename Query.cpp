//
// Created by Justin Chow on 6/27/22.
//

#include "Query.h"
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "DocumentParser.h"
#include <filesystem>
#include <fstream>
#include "porter2_stemmer/porter2_stemmer.h"
//test
using namespace std;

Query::Query() {
    getInfo();
}

void Query::getInfo() {


}
void Query::punctDestroyer(string &arg) {
    for(int i=0,len=arg.size();i<len;i++){
        if(!ispunct(arg[i])){
            arg[i]=tolower(arg[i]);
        }else{
           arg.erase(i--,1);
           len = arg.size();
        }
    }

}
unordered_map<int, int> Query::getInputLocations(string search) {
    unordered_map<int, int> page;

    char *token;
    vector<string> words;
    vector<string> input;
    unordered_set<string> terms = {"AND", "OR", "NOT", "ORG", "PERSON"};

    char *temp = search.data();
    token = strtok(temp, " ");
    while (token != nullptr) {
        string term(token);
        if (terms.find(term) == terms.end()) {
            punctDestroyer(term);
            Porter2Stemmer::stem(term);
            words.push_back(term);
        } else {
            words.push_back(term);
        }
        token = strtok(nullptr, " ");
    }

    int i = 0;
    while (i < words.size()) {
        if (terms.find(words[i]) != terms.end()) {
            if (words[i] == "ORG") {
                i++;
                try {
                    unordered_map<int, int> org = orgs.find(words[i]);
                    auto it = org.begin();
                    for (it; it != org.end(); it++) {
                        page.insert({it->first, it->second});
                    }
                }catch(exception){

                }
                i++;
                continue;
            } else if (words[i] == "PERSON") {
                i++;
                try {
                    unordered_map<int, int> temp = people.find(words[i]);
                    auto it = temp.begin();
                    for (it; it != temp.end(); it++) {
                        page.insert({it->first, it->second});
                    }
                }catch(exception){

                }
                i++;
                continue;
            } else if (words[i] == "AND") {
                try {
                    unordered_map<int, int> and1 = texts.find(words[i + 1]);

                    auto it = and1.begin();

                    unordered_map<int, int> and2 = texts.find(words[i + 2]);
                    auto is = and2.begin();
                    for (is; is != and2.end(); is++) {
                       if(and1.find(is->first)!=and1.end()){
                           page.insert({is->first,2*is->second});
                       }
                    }
                }catch(exception){

                    }
                i += 3;



                while (terms.find(words[i]) == terms.end() && i < words.size()) {
                    try{
                    unordered_map<int, int> temp = texts.find(words[i]);
                    auto ip = page.begin();
                    auto it = temp.begin();
                    for (ip; ip != page.end(); ip++) {
                        if (temp.find(ip->first) == temp.end()) {
                            page.erase(ip);
                            ip=page.begin();
                        }
                    }
                        if(page.size()==1) {
                            auto gg = page.begin();
                            if (temp.find(gg->first) != temp.end()) {
                                page.erase(gg);
                            }
                        }
                    i++;
                }catch(exception){
                    }
                }


               continue;
            } else if (words[i] == "OR") {
                try {

                    unordered_map<int, int> and2 = texts.find(words[i + 2]);
                    auto i2 = and2.begin();
                    for (i2; i2 != and2.end(); i2++) {
                            page.insert({i2->first, i2->second});
                        }

                }catch(exception){

                }
                try{
                    unordered_map<int, int> and1 = texts.find(words[i + 1]);
                    auto i1 = and1.begin();
                    for(i1;i1!= and1.end();i1++){
                        page.insert({i1->first,i1->second});
                    }
                }catch(exception){

                }
                i+=3;


            while (terms.find(words[i]) == terms.end() && i < words.size()) {
                try {
                    unordered_map<int, int> temp = texts.find(words[i]);
                    auto ip = temp.begin();
                    for (ip; ip != temp.end(); ip++) {
                        page.insert({ip->first, ip->second});
                    }
                }catch(exception){

                }

                i++;
            }

            continue;
        } else if (words[i] == "NOT") {
                try {

                    unordered_map<int, int> not1 = texts.find(words[i + 1]);


                  for(auto gg = page.begin();gg!= page.end();gg++){
                        if (not1.find(gg->first) != not1.end()) {
                            page.erase(gg);
                            gg=page.begin();
                        }
                    }
                  if(page.size()==1) {
                      auto ip = page.begin();
                      if (not1.find(ip->first) != not1.end()) {
                          page.erase(ip);
                      }
                  }
                }catch(exception){

                }
            i +=2;

        }

    } else {
            try {
                unordered_map<int, int> normal = texts.find(words[i]);
                auto iv = normal.begin();
                for (iv; iv != normal.end(); iv++) {
                    page.insert({iv->first, iv->second});
                }
            } catch(exception e){

            }

        i++;
    }

}

return page;
}
