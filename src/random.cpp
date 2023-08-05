#include "dictionary/random.h"

int getRandomNumber()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 144307); // 144307 is the number of words in the dictionary
    return dis(gen);
}

void viewRandomWord()
{
    std::ifstream fin;
    fin.open("../data/engengRandom.txt");
    int randomNum = getRandomNumber();
    std::string line;
    int currentLine = 0;
    while (std::getline(fin, line))
    {
        ++currentLine;
        if (currentLine == randomNum)
        {
            int sharpPos = line.find('#');
            int atPos = line.find_first_of('@');
            std::string keyWord = line.substr(0, sharpPos - 1);
            std::string wordType = line.substr(sharpPos + 1, atPos - sharpPos - 2);
            std::cout << keyWord << "\n";
            std::cout << "Type: " << wordType << "\n";
            std::cout << "Definition: " << "\n";
            int index = atPos + 1;
            while (index < line.length())
            {
                int nextAtPos = line.find('@', index);
                if (nextAtPos == std::string::npos)
                    break;
                std::string definition = line.substr(index, nextAtPos - index);
                std::cout << definition << "\n";
                index = nextAtPos + 1;
            }
        }
    }
}