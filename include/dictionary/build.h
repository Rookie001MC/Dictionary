#ifndef BUILD_H
#define BUILD_H

#include "globalVars/globalVars.h"
#include "trie.h"
#include "word.h"
#include <filesystem>

const std::string ENGENG = Resources::currentExeDir + "../tmp/engeng/";
const std::string ENGVIE = Resources::currentExeDir + "../tmp/engvie/";
const std::string VIEENG = Resources::currentExeDir + "../tmp/vieeng/";
const std::string EMOJI  = Resources::currentExeDir + "../tmp/emoji/";
const std::string SLANG  = Resources::currentExeDir + "../tmp/slang/";
const char ENGENGDELIMITER = '#';
const char ENGVIEDELIMITER = '$';
const char VIEENGDELIMITER = '$';
const char EMOJIDELIMITER = '$';
const char SLANGDELIMITER = '`';
void build(Dictionary &dict, Trie &trie);
void reset(Dictionary &dict, Trie &trie);

#endif