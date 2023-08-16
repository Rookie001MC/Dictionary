// main function currently used for testing. will be changed in the future
#include "dictionary/build.h"
#include "dictionary/trie.h"
#include "dictionary/word.h"

#include "dictionary/filePathHandler.h"
#include "dictionary/prebuildTries.h"
#include "dictionary/word.h"
#include "frontend/FrontendMain.h"
#include "frontend/ResourcesLoad.h"
#include "frontend/styles.h"
#include "globalVars/globalVars.h"

#include <chrono>
#include <iostream>

int main(int argc, const char *argv[])
{
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
    while (!WindowShouldClose())
    {
        frontend.start();
    }

    // Unload all resources and close the window
    unloadResources();
    clearPrebuiltTries();
    CloseWindow();
    std::cout << "\033[1;31mBye!\033[0m\n";

    return 0;
}

// // keep this for debugging
// int main(int argc, const char *argv[])
// {
//     auto start = std::chrono::high_resolution_clock::now();
//     Dictionary dict(Resources::currentExeDir +"../data/engvie.dict", 1);
//     Trie trie;
//     build(dict, trie);
//     // For random functions:
//     // Random random;
//     // random.setDictionary(&dict);
//     // random.setPath();
//     Word word;
//     std::string key;
//     std::cin >> key;
//     History history(Resources::currentExeDir+ "../tmp/engvie/history.txt");
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