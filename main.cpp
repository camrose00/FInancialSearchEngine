#include <iostream>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include "DocumentParser.h"
#include "porter2_stemmer/porter2_stemmer.h"
#include "AVLTree.h"
#include <chrono>
#include <unordered_map>
#include "Query.h"
#include "UI.h"

using namespace std::chrono;

int main(int argc, char **argv) {

      UI ui;
      ui.welcome(argv[1]);







}