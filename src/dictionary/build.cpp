/**
 * @file dictionary/build.cpp
 * @author Group7 - CS163 - 2022-2023
 * @brief Defining the functions related to processing the Tries.
 * @version 1.0
 */
#include "dictionary/build.h"

// Define the next key to be added
std::string nextKey;

/**
 * @brief Extract the data from the English-English dictionary file and insert it into the trie
 * 
 * @param dict The Dictionary object
 * @param trie The Trie object
 */
void extractEngEng(Dictionary &dict, Trie &trie)
{
    bool sign = false;
    while (!dict.eof())
    {
        Word word = dict.getWord();
        if (nextKey == "" && !sign)
            sign = true;
        else if (nextKey == "" && sign) // end of file
            break;
        trie.insert(word);
    }
    nextKey = "";
}

/**
 * @brief Extract the data from the English-Vietnamese dictionary file and insert it into the trie
 * 
 * @param dict 
 * @param trie 
 */
void extractEngVie(Dictionary &dict, Trie &trie)
{
    bool start = true;
    while (!dict.eof())
    {
        Word word = dict.getWord();
        if (start)
            start = false;
        else
            trie.insert(word);
    }
}

/**
 * @brief Extract the data from the Vietnamese-English dictionary file and insert it into the trie
 * 
 * @param dict 
 * @param trie 
 */
void extractVieEng(Dictionary &dict, Trie &trie)
{
    while (!dict.eof())
    {
        Word word       = dict.getWord();
        std::string key = word.getKey();
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        Word pre;
        if (!trie.search(key, pre))
            trie.insert(word);
        else
        {
            trie.remove(key);
            Word post;
            std::string type = pre.getType() + '/' + word.getType();
            word.setType(type);
            for (int i = 0; i < pre.getDefinitionCount(); ++i)
                post.addDefinition(pre.getDefinition(i));
            for (int i = 0; i < word.getDefinitionCount(); ++i)
                post.addDefinition(word.getDefinition(i));
            post.setKey(key);
            trie.insert(post);
        }
    }
}

/**
 * @brief Extract the data from the Emoji dictionary file and insert it into the trie
 * 
 * @param dict 
 * @param trie 
 */
void extractEmoji(Dictionary &dict, Trie &trie)
{
    while (!dict.eof())
    {
        Word word = dict.getWord();
        trie.insert(word);
    }
}

/**
 * @brief Extract the data from the Slang dictionary file and insert it into the trie
 * 
 * @param dict 
 * @param trie 
 */
void extractSlang(Dictionary &dict, Trie &trie)
{
    while (!dict.eof())
    {
        Word word = dict.getWord();
        Word cur;
        if (trie.search(word.getKey(), cur))
        {
            cur.addDefinition(word.getDefinition(0));
            trie.insert(cur);
            continue;
        }
        trie.insert(word);
    }
}

/**
 * @brief Build the trie from the dictionary file
 * 
 * @param dict The Dictionary object to be built
 * @param trie The Trie object to be built into
 */
void build(Dictionary &dict, Trie &trie)
{
    std::string path;
    char delimiter;
    switch (dict.getDictionaryType())
    {
        case 0:
            path      = ENGENG;
            delimiter = ENGENGDELIMITER;
            break;
        case 1:
            path      = ENGVIE;
            delimiter = ENGVIEDELIMITER;
            break;
        case 2:
            path      = VIEENG;
            delimiter = VIEENGDELIMITER;
            break;
        case 3:
            path      = EMOJI;
            delimiter = EMOJIDELIMITER;
            break;
        case 4:
            path      = SLANG;
            delimiter = SLANGDELIMITER;
            break;
    }
    if (!std::filesystem::exists(path))
        std::filesystem::create_directories(path);
    if (!std::filesystem::exists(path + "history.txt"))
    {
        std::ofstream fout(path + "history.txt");
        fout.close();
    }
    if (!std::filesystem::exists(path + "favourite.txt"))
    {
        std::ofstream fout(path + "favourite.txt");
        fout.close();
    }
    if (std::filesystem::exists(path + "data.dict"))
        trie.deserialize(path + "data.dict", delimiter);
    else
    {
        switch (dict.getDictionaryType())
        {
            case 0:
                extractEngEng(dict, trie);
                break;
            case 1:
                extractEngVie(dict, trie);
                break;
            case 2:
                extractVieEng(dict, trie);
                break;
            case 3:
                extractEmoji(dict, trie);
                break;
            case 4:
                extractSlang(dict, trie);
                break;
        }
        trie.serialize(path + "data.dict", delimiter);
    }
}

/**
 * @brief Save the current state of the trie into the dictionary file
 * 
 * @param dict The Dictionary object
 * @param trie The Trie object
 */
void save(Dictionary &dict, Trie &trie)
{
    std::string path;
    char delimiter;
    switch (dict.getDictionaryType())
    {
        case 0:
            path      = ENGENG;
            delimiter = ENGENGDELIMITER;
            break;
        case 1:
            path      = ENGVIE;
            delimiter = ENGVIEDELIMITER;
            break;
        case 2:
            path      = VIEENG;
            delimiter = VIEENGDELIMITER;
            break;
        case 3:
            path      = EMOJI;
            delimiter = EMOJIDELIMITER;
            break;
        case 4:
            path      = SLANG;
            delimiter = SLANGDELIMITER;
    }
    trie.serialize(path + "data.dict", delimiter);
}

/**
 * @brief Reset the dictionary to its initial state by deleting the data file and rebuilding the trie
 * 
 * @param dict 
 * @param trie 
 */
void reset(Dictionary &dict, Trie &trie)
{
    std::string path;
    char delimiter;
    switch (dict.getDictionaryType())
    {
        case 0:
            path      = ENGENG;
            delimiter = ENGENGDELIMITER;
            break;
        case 1:
            path      = ENGVIE;
            delimiter = ENGVIEDELIMITER;
            break;
        case 2:
            path      = VIEENG;
            delimiter = VIEENGDELIMITER;
            break;
        case 3:
            path      = EMOJI;
            delimiter = EMOJIDELIMITER;
            break;
        case 4:
            path      = SLANG;
            delimiter = SLANGDELIMITER;
    }
    dict.reset();
    trie.clear();
    trie.init();
    std::filesystem::remove(path + "history.txt");
    std::filesystem::remove(path + "favourite.txt");
    std::filesystem::remove(path + "data.dict");
    std::ofstream fout(path + "history.txt");
    fout.close();
    fout.open(path + "favourite.txt");
    fout.close();
    switch (dict.getDictionaryType())
    {
        case 0:
            extractEngEng(dict, trie);
            break;
        case 1:
            extractEngVie(dict, trie);
            break;
        case 2:
            extractVieEng(dict, trie);
            break;
        case 3:
            extractEmoji(dict, trie);
            break;
        case 4:
            extractSlang(dict, trie);
    }
    trie.serialize(path + "data.dict", delimiter);
}

/**
 * @brief Prebuild the tries for the first time the program is run 
 * 
 */
void prebuildDictionaries()
{
    std::cout << "\033[1;32mPrebuilding dictionaries...\033[0m\n";

    auto start = std::chrono::high_resolution_clock::now();
    build(engEng, PrebuiltTriesList[0]);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "engEng: \033[;32m" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\033[0m\n";

    start = std::chrono::high_resolution_clock::now();
    build(engVie, PrebuiltTriesList[1]);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "engVie: \033[;32m" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms\033[;0m\n";

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

/**
 * @brief Save the current state of the tries into the dictionary files when the program is closed
 * 
 */
void savePrebuiltTries()
{
    std::cout << "\033[1;31mSaving current state of the tries...\033[0m\n";
    save(engEng, PrebuiltTriesList[0]);
    save(engVie, PrebuiltTriesList[1]);
    save(vieEng, PrebuiltTriesList[2]);
    save(emoji, PrebuiltTriesList[3]);
    save(slang, PrebuiltTriesList[4]);
}

/**
 * @brief Clear the tries from memory when the program is closed
 * 
 */
void clearPrebuiltTries()
{
    std::cout << "\033[1;31mClearing prebuilt tries...\033[0m\n";
    for (auto &trie : PrebuiltTriesList)
    {
        trie.clear();
    }
}