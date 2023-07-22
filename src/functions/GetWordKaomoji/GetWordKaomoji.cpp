#include "GetWordKaomoji.h"

using json = nlohmann::json;

Word Dictionary::getWordKaomoji(std::ifstream &fin)
{

   if (!fin.is_open())
   {
      exit(1);
   }

   json j;
   fin >> j;

   std::string key = j.begin().key();
   std::string type = "kaomoji";
   std::vector<std::string> definitions = j[key]["original_tags"].get<std::vector<std::string>> ();
   std::vector<std::string> new_tags = j[key]["new_tags"].get<std::vector<std::string>> ();

   definitions.insert(definitions.end(), new_tags.begin(), new_tags.end());

   return Word(key, definitions, type);
}