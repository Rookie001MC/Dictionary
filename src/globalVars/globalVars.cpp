#include "globalVars/globalVars.h"

std::string dataDir               = Resources::currentExeDir + "../data/";
std::vector<std::string> dictDirs = {
    dataDir + "engeng.dict", dataDir + "engvie.dict", dataDir + "vieeng.dict",
    dataDir + "emoji.dict",  dataDir + "slang.dict",
};


Page CurrentState::currentPage = Page::DICT_WORD;
Word CurrentState::currentWord;
int *CurrentState::currentDict = new int{0};

Font Resources::titleFont;

Font Resources::displayFontRegular;
Font Resources::displayFontBold;

Font Resources::wordFontRegular;
Font Resources::wordFontBold;
Font Resources::wordFontItalic;

std::string Resources::currentExeDir;

Texture2D Resources::headerImage;

std::vector<Trie> PrebuiltTriesList(5);
