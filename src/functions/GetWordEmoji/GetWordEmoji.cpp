#include "GetWordEmoji.h"
using json = nlohmann::json;

Word Dictionary::getWordEmoji(std::ifstream& fin)
{
    if (!fin.is_open())
    {
        exit(1);
    }

    json j;
    fin >> j;

    std::string key  = j["emoji"];
    std::string type = j["category"];
    std::vector<std::string> definitions;
    definitions.push_back(j["description"]);

    return Word(key, definitions, type);
}

