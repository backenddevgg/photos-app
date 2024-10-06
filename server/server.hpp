#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define PORT 6001

#include <iostream>
#include <string>
#include <winsock2.h>
#include <filesystem>

namespace fs = std::filesystem;

#include "prepareResponse.hpp"

void initializeServer();
SOCKET createSocket();
void runServer(std::vector<fs::directory_entry>& fileTree);