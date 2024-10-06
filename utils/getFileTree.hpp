#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <iostream>

using std::vector, std::string;
namespace fs = std::filesystem;
using recursive_directory_iterator = fs::recursive_directory_iterator;

#define PATH "Fotos"

std::vector<fs::directory_entry> iterate();