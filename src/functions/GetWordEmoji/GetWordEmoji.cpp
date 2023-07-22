#include "GetWordEmoji.h"
using json = nlohmann::json;

Word Dictionary::getWordEmoji(std::ifstream& fin, int index)
{
    if (!fin.is_open())
    {
        exit(1);
    }

    json j;
    fin >> j;

    /*
[
  {
    "emoji": "😀",
    "description": "grinning face",
    "category": "smileys & emotion",
    "aliases": [
      "grinning"
    ],
    "tags": [
      "smile",
      "happy"
    ],
    "unicode_version": "6.1",
    "ios_version": "6.0"
  },
  ...
]
    */

    auto currentEmoji = j.begin() + index;
    std::string key = currentEmoji->at("emoji").get<std::string>();
    std::string type = currentEmoji->at("category").get<std::string>();
    // True definition should be the description of the emoji
    std::vector<std::string> definitions = { currentEmoji->at("description").get<std::string>() };
 
    return Word(key, definitions, type);
}

