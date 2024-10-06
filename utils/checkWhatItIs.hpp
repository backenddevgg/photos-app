#pragma once

#include <vector>
#include <filesystem>

#define IMAGE_EXTENSIONS std::vector({"png", "jpg", "jpeg", "bmp", "gif", "webp"})

void countFilesAndFolders(unsigned* directories, unsigned* files, std::vector<std::filesystem::directory_entry>& entries);
unsigned getNumberOfImages(std::vector<std::filesystem::directory_entry>& entries);

/**
 * @param entries directory from main
 * @return string that contains html-formatted!!! folder tree
 */
std::string getFolderTree(std::vector<std::filesystem::directory_entry>& entries);