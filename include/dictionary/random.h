#ifndef BACKEND_RANDOM_H
#define BACKEND_RANDOM_H

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
        // Helper function 
        int getRandomNumber();
        int randomInFour();

        Word viewRandomWord();                          // Function for viewing a random word

        // The structure of the vector<string> 
        // index 0: question (either a key word or a definition)
        // index 1: correct answer (either a key word or a definition)
        // index 2-3-4: wrong answer (either a key word or a definition)
        
        std::vector<std::string> random4DefinitionsAnd1KeyWord();  // Function returns a vector<string> containing 
                                                                   // 4 definitions and 1 key word
            
        std::vector<std::string> random4KeyWordsAnd1Def();      // Function return a vector<string> containing
                                                                // 4 key words and 1 definition

        // void quizWith4Definitions();
        // void quizWith4KeyWords();

};


// Quiz
std::string get1stDefinitionFromText(const std::string &line);
std::string getKeyWordFromText(const std::string &line);

// Reference function for the flow of the quiz
// void quizWith4Definitions();
// void quizWith4KeyWords();

#endif