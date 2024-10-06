#include "./server.hpp"

#pragma comment(lib, "ws2_32.lib")  // Link with the Winsock library

using std::cout, std::endl;

void initializeServer() {
    WSADATA wsaData;
    int wsResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsResult != 0) {
        std::cerr << "WSAStartup failed: " << wsResult << endl;
        exit(1);
    }
}

SOCKET createSocket() {
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket: " << WSAGetLastError() << endl;
        WSACleanup();
        exit(1);
    }
    return serverSocket;
}

std::string getHeader(const std::string& request, std::string line) {
    size_t pos = request.find(line);
    
    if (pos != std::string::npos) {
        size_t start = pos + line.length();
        size_t end = request.find("\r\n", start); // Find end of the line
        return request.substr(start, end - start); // Extract the Referer value
    }
    
    return ""; // Return an empty string if not found
}

std::string getGET(const std::string& request) {
    std::string get = getHeader(request, "GET ");
    std::size_t lastSpace = get.find_last_of(" ");
    return get.substr(0, lastSpace);
}
std::string getHost(const std::string& request) {
    return getHeader(request, "Host: ");
}
std::string getRoute(const std::string& request) {
    return getGET(request);
}

void runServer(std::vector<fs::directory_entry>& fileTree) {
    // Initialize Winsock
    initializeServer();

    // Create a socket
    SOCKET serverSocket = createSocket();

    // Bind the socket to an IP address and port
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Bind to any IP address
    serverAddr.sin_port = htons(PORT);        // Bind to port

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        exit(1);
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << endl;
        closesocket(serverSocket);
        WSACleanup();
        exit(1);
    }

    cout << "Server is listening on port " << PORT << "..." << endl;

    while (true) {
        // Accept an incoming connection
        sockaddr_in clientAddr;
        int clientSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << WSAGetLastError() << endl;
            continue;  // Keep listening for other connections
        }

        // Receive data from the client
        char buffer[4096];
        int bytesReceived = recv(clientSocket, buffer, 4096, 0);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Receive failed: " << WSAGetLastError() << endl;
            closesocket(clientSocket);
            continue;
        }

        std::string request(buffer, bytesReceived);
        std::string route = getRoute(buffer);

        cout << "Called: " << route << endl;

        // Send HTTP response
        std::string httpResponse = prepareResponse(route, fileTree);

        send(clientSocket, httpResponse.c_str(), httpResponse.size(), 0);

        // Close the client connection, but keep the server socket open for new clients
        closesocket(clientSocket);
    }

    // Cleanup the server socket and Winsock (this will only happen when the server stops)
    closesocket(serverSocket);
    WSACleanup();
}
