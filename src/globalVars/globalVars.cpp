/**
 * @file globalVars.cpp
 * @author Group07 - CS163 - 2022-2023
 * @brief File to declare all the global variables that are shared throughout the project
 * @version 1.0
 * 
 */

#include "globalVars/globalVars.h"
#include "dictionary/history.h"
#include "dictionary/word.h"

// Location of the dictionary dataset files
std::string dataDir               = Resources::currentExeDir + "../data/";

// Declare the possible dictionary files
std::vector<std::string> dictDirs = {
    dataDir + "engeng.dict", dataDir + "engvie.dict", dataDir + "vieeng.dict",
    dataDir + "emoji.dict",  dataDir + "slang.dict",
};

// Declare the possible history files
std::vector<std::string> historyDirectories = {
    Resources::currentExeDir + "../tmp/engeng/history.txt", Resources::currentExeDir + "../tmp/engvie/history.txt",
    Resources::currentExeDir + "../tmp/vieeng/history.txt", Resources::currentExeDir + "../tmp/emoji/history.txt",
    Resources::currentExeDir + "../tmp/slang/history.txt"};

// Declare the possible favorite files
std::vector<std::string> favoritesDirectories = {
    Resources::currentExeDir + "../tmp/engeng/favourite.txt", Resources::currentExeDir + "../tmp/engvie/favourite.txt",
    Resources::currentExeDir + "../tmp/vieeng/favourite.txt", Resources::currentExeDir + "../tmp/emoji/favourite.txt",
    Resources::currentExeDir + "../tmp/slang/favourite.txt"};

// Initialize the dictionaries
Dictionary engEng = Dictionary(dictDirs[0], 0);
Dictionary engVie = Dictionary(dictDirs[1], 1);
Dictionary vieEng = Dictionary(dictDirs[2], 2);
Dictionary emoji  = Dictionary(dictDirs[3], 3);
Dictionary slang  = Dictionary(dictDirs[4], 4);

// Set the global variables that keep track of the state of the program
Page CurrentState::currentPage = Page::DICT_WORD;
Word CurrentState::currentWord;
int *CurrentState::currentDict = new int{0};
Dictionary *CurrentState::currentDictObject = &engEng;

History* currentDictHistory;
History* currentDictFavorites;
Trie currentTrie;

// Global variables that store the resources in memory
Font Resources::titleFont;

Font Resources::displayFontRegular;
Font Resources::displayFontBold;

Font Resources::wordFontRegular;
Font Resources::wordFontBold;
Font Resources::wordFontItalic;

Texture2D Resources::headerImage;

// The location of the program executable
std::string Resources::currentExeDir;

// The list of prebuilt tries
std::vector<Trie> PrebuiltTriesList(5);
