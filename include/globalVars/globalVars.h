#ifndef GLOBAL_VARS
#define GLOBAL_VARS

#include "dictionary/filePathHandler.h"
#include "dictionary/history.h"
#include "dictionary/trie.h"
#include "dictionary/word.h"
#include "raylib.h"
#include <vector>

enum Page
{
    DICT_WORD = 0,    // Main menu
    DICT_DEF_SEARCH,  // Definition search
    DICT_FAVORITES,   // Favorites
    DICT_HISTORY,     // History
    DICT_GAME,        // Game
    SINGLE_WORD_INFO, // Information of single word
};
struct Resources
{
    static std::string currentExeDir;
    static Font titleFont;

    static Font displayFontRegular;
    static Font displayFontBold;

    static Font wordFontRegular;
    static Font wordFontBold;
    static Font wordFontItalic;

    static Texture2D headerImage;
};
struct CurrentState
{
    static Page
        currentPage; // Current page (e.g. what search mode it's currently on, word search, definition search, etc.)
    static Word currentWord;
    static int *currentDict;
    static Dictionary *currentDictObject;
    static History currentDictHistory;
    static History currentDictFavorites;
    static Trie currentTrie;
};

struct PrebuiltTries
{
    static Trie engEng;
    static Trie engVie;
    static Trie vieEng;
    static Trie emoji;
    static Trie slang;
};

extern std::vector<Trie> PrebuiltTriesList;

extern std::vector<std::string> dictDirs;

extern std::vector<std::string> historyDirectories;
extern std::vector<std::string> favoritesDirectories;

extern Dictionary engEng;
extern Dictionary engVie;
extern Dictionary vieEng;
extern Dictionary emoji;
extern Dictionary slang;

#endif