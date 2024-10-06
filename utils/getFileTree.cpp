#include "./getFileTree.hpp"

std::vector<fs::directory_entry> iterate() {
    std::vector<fs::directory_entry> result;

    try {
        fs::current_path(fs::path(PATH));
        std::cout << "Current path changed to: " << fs::current_path() << '\n';
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return result;  // Return an empty vector on error
    }

    for (fs::directory_entry const& dir_entry : fs::recursive_directory_iterator(".")) {
        // result.push_back(dir_entry);  // Properly converting path to string
        result.push_back(dir_entry);
    }

    return result;
}