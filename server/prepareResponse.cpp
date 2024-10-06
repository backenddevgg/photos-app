#include "prepareResponse.hpp"

#define NONE_VALUE "NONE"

string renderEHTML(string html, vector<string> keys, vector<string> contentOfKeys) {
    if(!(keys.size() <= contentOfKeys.size())) {
        std::cerr << "LENGTH OF KEYS IS MORE THAN IT'S CONTENT! (renderEHTML)" << std::endl;
        return "";
    }
    for(unsigned short i = 0; i < keys.size(); i++) {
        unsigned first = html.find("{{" + keys.at(i) + "}}");
        unsigned len = keys.at(i).length() + 4;
        html.replace(first, len, contentOfKeys.at(i));
    }
    return html;
}

string getHTMLfile(const string&& fileName) {
    ifstream file;
    file.open(PAGES_FOLDER_PATH + fileName);
    if(!file.is_open()) {
        std::cerr << "UNABLE TO OPEN HTML FILE WITH NAME \"" << fileName << "\".\nIs the pages folder in the right position?" << std::endl;
        return "<center><h1><em>500</em> SERVER ERROR</h1></center>";
    }
    string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
}

string prepareStatusCode(unsigned short&& code) {
    string txt;
    switch(code) {
        case 200:
            txt = "OK";
        break;
        case 404:
            txt = "Not Found";
        break;
        case 418:
            txt = "I'm a teapot";
        break;
        case 500:
            txt = "Server Error";
        break;
        default:
            txt = "OK";
    }
    // REAL GARBAGE:
    char s[50];
    sprintf(s, "HTTP/1.1 %hu %s\r\nContent-Type: text/html\r\n\r\n", code, txt);
    string str = "";
    str.append(s);
    return str;
}
string prepareResponse(const string& route, std::vector<fs::directory_entry>& fileTree) {
    string r = prepareStatusCode(200);
    if(route == "/"){
        string fileTreeFolders = getFolderTree(fileTree);
        vector<string> keys = {"FILETREE"};
        vector<string> contents = {fileTreeFolders};
        r.append(renderEHTML(getHTMLfile("index.e.html"), keys, contents));
    }
    else{
        r = prepareStatusCode(404) + string("<center><h1><em>404</em> <u>NOT</u> FOUND</h1></center>");
    }
    return r;
}