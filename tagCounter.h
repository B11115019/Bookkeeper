#pragma once
#include <unordered_map>
#include "Definitions.h"

void init();
void addTag(std::string& tag);
void removeTag(std::string& tag);
U_Int32 getTagCount(std::string& tag);
std::vector<std::string> getAllTag();
