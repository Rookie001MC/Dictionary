#include <random>
#include <iostream>
#include <fstream>
#include <string>

// View random word
int getRandomNumber();
void viewRandomWord();

// Quiz
int randomInFour();
std::string get1stDefinitionFromText(const std::string &line);
void random4Definitions();
void quizWith4Definitions();
void random4KeyWords();
std::string getKeyWordFromText(const std::string &line);
void quizWith4KeyWords();