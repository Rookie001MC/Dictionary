// main function currently used for testing. will be changed in the future
#include <iostream>
#include "dictionary/history.h"
#include "dictionary/trie.h"
#include "dictionary/word.h"
#include "dictionary/build.h"
#include <chrono>

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    Dictionary dict("../data/engeng.dict", 0);
    Trie trie;
    build(dict, trie);
    Word word;
    trie.search("determination", word);
    std::cout << word.getKey() << ' ' << word.getType() << '\n';
    std::vector<std::string> defs = word.getDefinitions();
    for (int i = 0; i < defs.size(); ++i)
        std::cout << defs.at(i) << '\n';
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // std::cout << duration;
    return 0;
}