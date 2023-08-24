#include "dictionary/build.h"

std::string nextKey;

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

void extractEmoji(Dictionary &dict, Trie &trie)
{
    while (!dict.eof())
    {
        Word word = dict.getWord();
        trie.insert(word);
    }
}

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
            break;
    }
    trie.serialize(path + "data.dict", delimiter);
}

void reset(Dictionary &dict, Trie &trie)
{
    std::string path;
    switch (dict.getDictionaryType())
    {
        case 0:
            path = ENGENG;
            break;
        case 1:
            path = ENGVIE;
            break;
        case 2:
            path = VIEENG;
            break;
        case 3:
            path = EMOJI;
            break;
        case 4:
            path = SLANG;
            break;
    }
    dict.reset();
    trie.clear();
    trie.init();
    std::filesystem::remove_all(path);
    std::filesystem::create_directories(path);
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
}

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
              << "ms\033[;32m\n";

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

void savePrebuiltTries()
{
    std::cout << "\033[1;31mSaving current state of the tries...\033[0m\n";
    save(engEng, PrebuiltTriesList[0]);
    save(engVie, PrebuiltTriesList[1]);
    save(vieEng, PrebuiltTriesList[2]);
    save(emoji, PrebuiltTriesList[3]);
    save(slang, PrebuiltTriesList[4]);
}

void clearPrebuiltTries()
{
    std::cout << "\033[1;31mClearing prebuilt tries...\033[0m\n";
    for (auto &trie : PrebuiltTriesList)
    {
        trie.clear();
    }
}