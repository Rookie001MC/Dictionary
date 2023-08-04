#ifndef FRONTEND_PAGE_WORD
#define FRONTEND_PAGE_WORD

#include <iostream>
#include <cstring>
#include <vector>
#include "raylib.h"
#include "frontend/styles.h"
#include "dictionary/word.h"

class WordPage {
    private:
        bool SearchEdit = false;
        char SearchInput[101] = "";
        Rectangle rec_result[20];
        Rectangle rec_dictionary{1030, 115, 155, 65};
        Rectangle rec_reset{740, 115, 135, 65};
        Rectangle rec_random{885, 115, 135, 65};
        Rectangle rec_search{305, 115, 420, 65};
        short menuChosen = 0;
        bool dropDowmBox = false, confirmResetBox = false, addWordButton = false;
        std::vector<Word *> words;
        std::string text;
    public:
        WordPage();
        void draw();
        void update();
        void resetBox();
        void addWord();
        ~WordPage() {
        }

};

#endif