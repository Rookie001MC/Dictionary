#include "globalVars/globalVars.h"
#include "dictionary/history.h"
#include "dictionary/word.h"

std::string dataDir               = Resources::currentExeDir + "../data/";
std::vector<std::string> dictDirs = {
    dataDir + "engeng.dict", dataDir + "engvie.dict", dataDir + "vieeng.dict",
    dataDir + "emoji.dict",  dataDir + "slang.dict",
};

// Declare the possible history files
std::vector<std::string> historyDirectories = {
    Resources::currentExeDir + "../tmp/engeng/history.txt", Resources::currentExeDir + "../tmp/engvie/history.txt",
    Resources::currentExeDir + "../tmp/vieeng/history.txt", Resources::currentExeDir + "../tmp/emoji/history.txt",
    Resources::currentExeDir + "../tmp/slang/history.txt"};

std::vector<std::string> favoritesDirectories = {
    Resources::currentExeDir + "../tmp/engeng/favourite.txt", Resources::currentExeDir + "../tmp/engvie/favourite.txt",
    Resources::currentExeDir + "../tmp/vieeng/favourite.txt", Resources::currentExeDir + "../tmp/emoji/favourite.txt",
    Resources::currentExeDir + "../tmp/slang/favourite.txt"};

Dictionary engEng = Dictionary(dictDirs[0], 0);
Dictionary engVie = Dictionary(dictDirs[1], 1);
Dictionary vieEng = Dictionary(dictDirs[2], 2);
Dictionary emoji  = Dictionary(dictDirs[3], 3);
Dictionary slang  = Dictionary(dictDirs[4], 4);

Page CurrentState::currentPage = Page::DICT_WORD;
Word CurrentState::currentWord;
int *CurrentState::currentDict = new int{0};
Dictionary *CurrentState::currentDictObject = &engEng;
History CurrentState::currentDictHistory = History(historyDirectories[*CurrentState::currentDict], 0);
History CurrentState::currentDictFavorites = History(favoritesDirectories[*CurrentState::currentDict], 1);
Trie CurrentState::currentTrie;

Font Resources::titleFont;

Font Resources::displayFontRegular;
Font Resources::displayFontBold;

Font Resources::wordFontRegular;
Font Resources::wordFontBold;
Font Resources::wordFontItalic;

std::string Resources::currentExeDir;

Texture2D Resources::headerImage;

std::vector<Trie> PrebuiltTriesList(5);
