/**
 * @file main.cpp
 * @author Group7 - CS163 - 2022-2023
 * @brief The entrypoint to the program.
 * @version 1.0
 * 
 */

#include "dictionary/build.h"
#include "dictionary/filePathHandler.h"
#include "dictionary/history.h"
#include "dictionary/trie.h"
#include "dictionary/word.h"
#include "frontend/FrontendMain.h"
#include "frontend/ResourcesLoad.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"
#include "raylib.h"
#include <chrono>
#include <iostream>

int main(int argc, const char *argv[])
{
    // Supress all debug messages on release
    #ifndef NDEBUG
    SetTraceLogLevel(LOG_ALL);
    #else
    SetTraceLogLevel(LOG_ERROR);
    #endif

    // Set the current executable directory.
    // This is used to avoid directory problems when running the executable from different locations.
    Resources::currentExeDir = getExeDir(argv[0]);

    // Prebuild dictionaries
    prebuildDictionaries();

    // Start the frontend
    std::cout << "\033[1;32mStarting Dictionary...\033[0m\n";
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CS163 Project - The Dictionary of Everything?");
    SetTargetFPS(60);
    loadResources();
    FrontendMain frontend;

    // These are used to keep track of the global data of the dictionaries
    currentTrie = PrebuiltTriesList.at(*CurrentState::currentDict);
    currentDictHistory = new History(historyDirectories.at(*CurrentState::currentDict), 0);
    currentDictFavorites = new History(favoritesDirectories.at(*CurrentState::currentDict), 1);

    while (!WindowShouldClose())
    {
        frontend.start();
    }

    // Unload all resources and close the window
    unloadResources();
    savePrebuiltTries();
    clearPrebuiltTries();
    CloseWindow();
    std::cout << "\033[1;31mBye!\033[0m\n";

    return 0;
}

// keep this for debugging
// int main(int argc, const char *argv[])
// {
//     // auto start = std::chrono::high_resolution_clock::now();
//     Dictionary dict(Resources::currentExeDir +"../data/engeng.dict", 0);
//     Trie trie;
//     build(dict, trie);
//     // UserData user(&trie, & dict);
//     // Word w("idirius", "name", "thong");
//     // w.addDefinition("Nguyen");
//     // w.addDefinition("Vo");
//     // w.addDefinition("Hoang");
//     // w.addDefinition("Thong");
//     // Word ww("canhcut", "name", "khoa");
//     // trie.insert(w);
//     // trie.insert(ww);
//     // For random functions:
//     // Random random;
//     // random.setDictionary(&dict);
//     // random.setPath();
//     //  std::string key;
//     // std::cin >> key;
//     //History history(Resources::currentExeDir+ "../tmp/engvie/history.txt");
//     Word word;
//     if (trie.search("canhcut", word))
//     for (int i = 0; i < word.getDefinitionCount(); ++i)
//         std::cout << word.getDefinition(i) << '\n';
//     // trie.insert(word);
//     // std::vector<Word> wordlist = trie.wordSuggest("cas");
//     // for (int i = 0; i < wordlist.size(); ++i)
//     //     std::cout << wordlist.at(i).getKey() << ' ' << wordlist.at(i).getType() << '\n';
//     // wordlist.clear();
//     // wordlist = trie.wordSuggest("ma");
//     // for (int i = 0; i < wordlist.size(); ++i)
//     //     std::cout << wordlist.at(i).getKey() << ' ' << wordlist.at(i).getType() << '\n';
//     //     std::vector<std::string> defs = wordlist.at(i).getDefinitions();
//     //     for (int i = 0; i < defs.size(); ++i)
//     //         std::cout << defs.at(i) << '\n';
//     //     std::cout << std::endl;
//     // }
//     // history.save();
//     // auto stop     = std::chrono::high_resolution_clock::now();
//     // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//     // std::cout << "build duration" << duration;
//     save(dict, trie);
//     return 0;
// }