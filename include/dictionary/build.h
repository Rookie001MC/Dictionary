#ifndef BUILD_H
#define BUILD_H

#include "trie.h"
#include "word.h"
#include <filesystem>

const std::string ENGENG = "../tmp/engeng/";
const std::string ENGVIE = "../tmp/engvie/";
const std::string VIEENG = "../tmp/vieeng/";
const std::string EMOJI  = "../tmp/emoji/";
const std::string SLANG  = "../tmp/slang/";

void build(Dictionary &dict, Trie &trie);

#endif