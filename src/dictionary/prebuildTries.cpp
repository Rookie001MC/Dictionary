#include "dictionary/prebuildTries.h"

void prebuildDictionaries()
{
    std::cout << "\033[1;32mPrebuilding dictionaries...\033[0m\n";

    std::string dataDir               = Resources::currentExeDir + "../data/";
    std::vector<std::string> dictDirs = {
        dataDir + "engeng.dict", dataDir + "engvie.dict", dataDir + "vieeng.dict",
        dataDir + "slang.dict",  dataDir + "emoji.dict",
    };

    Dictionary engEng = Dictionary(dictDirs[0], 0);
    Dictionary engVie = Dictionary(dictDirs[1], 1);
    Dictionary vieEng = Dictionary(dictDirs[2], 2);
    // Dictionary emoji = Dictionary(dictDirs[3], 3);
    Dictionary slang = Dictionary(dictDirs[4], 3);

    auto start = std::chrono::high_resolution_clock::now();
    build(engEng, PrebuiltTriesList[0]);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "engEng: \033[;32m" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\033[0m\n";

    /*     start = std::chrono::high_resolution_clock::now();
        build(engVie, *PrebuiltTries::engVie);
        end = std::chrono::high_resolution_clock::now();
        std::cout << "engVie: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
     */

    start = std::chrono::high_resolution_clock::now();
    build(vieEng, PrebuiltTriesList[2]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "vieEng: \033[;32m" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\033[0m\n";

    /*     start = std::chrono::high_resolution_clock::now();
        build(emoji, *PrebuiltTries::emoji);
        end = std::chrono::high_resolution_clock::now();
        std::cout << "emoji: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
     */

    start = std::chrono::high_resolution_clock::now();
    build(slang, PrebuiltTriesList[3]);
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
