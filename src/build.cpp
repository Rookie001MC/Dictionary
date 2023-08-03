#include "dictionary/build.h"
#include <iostream>
#include <algorithm>

std::string nextKey;

void extractEngEng(Dictionary &dict, Trie &trie) {
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

void extractVieEng(Dictionary &dict, Trie &trie) {
    while (!dict.eof()) {
        Word word = dict.getWord();
        std::string key = word.getKey();
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        Word pre;
        if (trie.search(key, pre))
            trie.insert(word);
        else {
            trie.remove(key);
            Word post;
            std::string type = pre.getType() + '/' + word.getType();
            word.setType(type);
            for (int i = 0; i < pre.getDefinitionCount(); ++i)
                post.addDefinition(pre.getDefinition(i));
            for (int i = 0; i < word.getDefinitionCount(); ++i)
                post.addDefinition(word.getDefinition(i));
            word.setKey(pre.getKey());
            trie.insert(post);
        }
    }
}

void build(Dictionary &dict, Trie &trie)
{
    std::string path;
    char delimiter;
    switch (dict.getDictionaryType())
    {
        case 0:
            path = ENGENG;
            delimiter = ENGENGDELIMITER;
            break;
        case 1:
            path = ENGVIE;
            delimiter = ENGVIEDELIMITER;
            break;
        case 2:
            path = VIEENG;
            delimiter = VIEENGDELIMITER;
            break;
        case 3:
            path = EMOJI;
            delimiter = EMOJIDELIMITER;
            break;
        case 4:
            path = SLANG;
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
                
                break;
            case 4:
                
                break;
        }
        trie.serialize(path + "data.dict", delimiter);
    }
}