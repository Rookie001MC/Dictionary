#include "dictionary/prebuildTries.h"
#include "globalVars/globalVars.h"

void prebuildDictionaries()
{
    std::cout << "\033[1;32mPrebuilding dictionaries...\033[0m\n";

    Dictionary engEng = Dictionary(dictDirs[0], 0);
    Dictionary engVie = Dictionary(dictDirs[1], 1);
    Dictionary vieEng = Dictionary(dictDirs[2], 2);
    Dictionary emoji = Dictionary(dictDirs[3], 3);
    Dictionary slang = Dictionary(dictDirs[4], 4);

    auto start = std::chrono::high_resolution_clock::now();
    build(engEng, PrebuiltTriesList[0]);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "engEng: \033[;32m" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\033[0m\n";

    start = std::chrono::high_resolution_clock::now();
    build(engVie, PrebuiltTriesList[1]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "engVie: \033[;32m" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\033[;32m\n";
     

    start = std::chrono::high_resolution_clock::now();
    build(vieEng, PrebuiltTriesList[2]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "vieEng: \033[;32m" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\033[0m\n";

    start = std::chrono::high_resolution_clock::now();
    build(emoji, PrebuiltTriesList[3]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "emoji: \033[;32m" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\033[0m\n";
    

    start = std::chrono::high_resolution_clock::now();
    build(slang, PrebuiltTriesList[4]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "slang: \033[;32m" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\033[0m\n";
}

void clearPrebuiltTries()
{
    std::cout << "\033[1;31mClearing prebuilt tries...\033[0m\n";
    for (auto &trie : PrebuiltTriesList)
    {
        trie.clear();
    }
}
