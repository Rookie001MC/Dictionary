#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include "word.h"

class Random{
    private:
        Dictionary* dictionary = nullptr;         // dictionary
        int mode;                       // mode of dataset
        std::string path;               // path to dataset
    public:
        void setDictionary(Dictionary* dict);
        void setMode(Dictionary* dict);
        int getMode();
        void setPath();
        std::string getPath();
        int getRandomNumber();
        int randomInFour();
        Word viewRandomWord();
        void random4Definitions();
        void quizWith4Definitions();
        void random4KeyWords();
        void quizWith4KeyWords();

};
// View random word
void viewRandomWord();

// Quiz
int randomInFour();
std::string get1stDefinitionFromText(const std::string &line);
void random4Definitions();
void quizWith4Definitions();
void random4KeyWords();
std::string getKeyWordFromText(const std::string &line);
void quizWith4KeyWords();