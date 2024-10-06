#pragma once

#define PAGES_FOLDER_PATH "D:\\Dokumente\\dev\\C++\\photos\\pages\\"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>

#include "../utils/checkWhatItIs.hpp"
namespace fs = std::filesystem;

using std::string, std::ifstream, std::vector;

string renderEHTML(string html, vector<string> keys, vector<string> contentOfKeys);

/**
 * @param fileName name of file INSIDE OF "pages" FOLDER with relative path to that folder
 * @return content of file as string if exists and otherwise 500 server error
 */
string getHTMLfile(const string&& fileName);

string prepareStatusCode(unsigned short&& code);

string prepareResponse(const string& route, std::vector<fs::directory_entry>& fileTree);