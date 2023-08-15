#include "globalVars/globalVars.h"
#include "dictionary/filePathHandler.h"

Page CurrentState::currentPage = Page::DICT_WORD;
Word *CurrentState::currentWord;

Font Resources::titleFont;

Font Resources::displayFontRegular;
Font Resources::displayFontBold;

Font Resources::wordFontRegular;
Font Resources::wordFontBold;
Font Resources::wordFontItalic;

std::string Resources::currentExeDir;

Texture2D Resources::headerImage;

Trie* PrebuiltTries::engEng = new Trie;
Trie* PrebuiltTries::engVie = new Trie;
Trie* PrebuiltTries::vieEng = new Trie;
Trie* PrebuiltTries::emoji = new Trie;
Trie* PrebuiltTries::slang = new Trie;

Word selectedWord;