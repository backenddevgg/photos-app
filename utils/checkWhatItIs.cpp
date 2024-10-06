#include "./checkWhatItIs.hpp"

void countFilesAndFolders(unsigned* directories, unsigned* files, std::vector<std::filesystem::directory_entry>& entries) {
    for (std::filesystem::directory_entry entry: entries) {
        if (entry.is_directory()) (*directories)++;
        else if (entry.is_regular_file()) (*files)++;
    }
}

unsigned getNumberOfImages(std::vector<std::filesystem::directory_entry>& entries) {
    unsigned countImageFiles = 0;
    for (std::filesystem::directory_entry entry: entries) {
        if (entry.is_regular_file()) {
            std::string extension = entry.path().extension().string();
            for (std::string ext: IMAGE_EXTENSIONS) {
                if (extension == "." + ext) {
                    countImageFiles++;
                    break;
                }
            }
        }
    }
    return countImageFiles;
}

std::string getFolderTree(std::vector<std::filesystem::directory_entry>& entries) {
    std::string tree = "";
    for(std::filesystem::directory_entry entry: entries) {
        if(entry.is_directory()) {
            tree.append("<span class=\"fileTree directoryTree\">" + entry.path().string() + "</span>");
        }
    }
    return tree;
}