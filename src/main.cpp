// main function currently used for testing. will be changed in the future
#include "boost/filesystem.hpp"
#include "boost/filesystem/operations.hpp"
#include "dictionary/build.h"
#include "dictionary/history.h"
#include "dictionary/trie.h"
#include "dictionary/word.h"
#include <chrono>
#include <iostream>

#include "frontend/FrontendMain.h"
#include "frontend/ResourcesLoad.h"
#include "frontend/styles.h"

int main(int argc, const char *argv[])
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CS163 Project - The Dictionary of Everything?");
    SetTargetFPS(60);
    loadResources(argv[0]);
    FrontendMain frontend;
    while(!WindowShouldClose())
    {
        frontend.start();
    }
    unloadResources();
    CloseWindow();
    return 0;
}

// // keep this for debugging
// int main(int argc, const char *argv[])
// {
//     auto start = std::chrono::high_resolution_clock::now();
//     Dictionary dict("../data/vieeng.dict", 2);
//     std::cout << boost::filesystem::file_size("../data/vieeng.dict") << '\n';
//     Trie trie;
//     build(dict, trie);
//     Word word;
//     std::string key;
//     std::cin >> key;
//     History history("../tmp/vieeng/history.txt");
//     if (trie.search(key, word))
//         history.add(key);
//     for (int i = 0; i < word.getDefinitionCount(); ++i)
//         std::cout << word.getDefinition(i) << '\n';
//     // std::vector<Word> wordlist = trie.wordSuggest(key);
//     // for (int i = 0; i < wordlist.size(); ++i) {
//     //     std::cout << wordlist.at(i).getKey() << ' ' << wordlist.at(i).getType() << '\n';
//     //     std::vector<std::string> defs = wordlist.at(i).getDefinitions();
//     //     for (int i = 0; i < defs.size(); ++i)
//     //         std::cout << defs.at(i) << '\n';
//     //     std::cout << std::endl;
//     // }
//     history.save();
//     auto stop     = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//     std::cout << "build duration" << duration;
//     return 0;
// }