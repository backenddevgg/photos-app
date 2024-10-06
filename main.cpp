#include <iostream>

#include "./utils/getFileTree.hpp"
#include "./utils/checkWhatItIs.hpp"
#include "./server/server.hpp"

using std::cout, std::endl;

int main() {

    cout << "Running..." << endl;
    // get directory tree
    std::vector<fs::directory_entry> directoryContent = iterate();

    // analyze directory
    cout << "\nANALYSIS\n";
    cout << "Size of directory: " << directoryContent.size() << " entries" << "\n";
    unsigned countFiles = 0, countFolders = 0; countFilesAndFolders(&countFolders, &countFiles, directoryContent);
    unsigned countImageFiles = getNumberOfImages(directoryContent);
    cout << "Number of folders: " << countFolders << "\nNumber of files: " << countFiles << "\n";
    cout << "Number of image files: " << countImageFiles << "\n" << endl;

    // for (fs::directory_entry const& dir_entry: directoryContent) {
    //     cout << dir_entry << endl;
    // }

    // start web server
    runServer(directoryContent);

    return 0;
}