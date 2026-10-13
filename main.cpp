#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <cstring>
#include <ctime>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>


#include "define.h"
#include "send.h"
#include "metadata.h"
#include "receive.h"
#include "requests.h"
#include "init.h"
#include "files.h"


int running = 1;

int main(void){
    WSADATA wsaData;
    if(init_WSA(&wsaData)){
        std::cout << "winsock dll not found" << std::endl;
        return 1;
    } else {
        std::cout << "success" << std::endl;
        std::cout << "the status: " << wsaData.szSystemStatus << std::endl;
    }

    //creating the server socket to wait for clients
    SOCKET serversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serversocket == INVALID_SOCKET){
        std::cout << "problem" << std::endl;
        WSACleanup();
        return 2;
    } else {
        std::cout << "success" << '\n';
    }


    Config config = load_config("config.txt");

    std::cout << "PORT: "         << config.port 
              << "\nIndex file: " << config.index_file 
              << "\nRoot path: "  << config.root_path 
              << '\n';

    SOCKADDR_IN service = init_service(AF_INET, config.port, INADDR_ANY);

    if(bind(serversocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR){
        std::cout << "bind problem | " << WSAGetLastError() << std::endl;
        WSACleanup();
        closesocket(serversocket);
        return 3;
    } else {
        std::cout << "bind success" << '\n';
    }

    //listening for clients on the server socket 
    if(listen(serversocket, MAX_CLIENTS) == SOCKET_ERROR){
        std::cout << "listen() failed | " << WSAGetLastError() << std::endl;
        WSACleanup();
        closesocket(serversocket);
        return 4;
    } else {
        std::cout << "listening..." << '\n';
    }

    //infinit loop so that the server keep running even when the client disconnect
    while(running){ 
        SOCKET new_socket = accept_connection(serversocket);
        if (new_socket != INVALID_SOCKET) std::cout << "Connection accepted\n";
        std::string msg;
        int num_bytes = recieve_request(new_socket, msg);
        if (num_bytes > 0)  msg[num_bytes] = '\0';
        if (num_bytes == SOCKET_ERROR){
            std::cout << "couldn't receive the request | "<< WSAGetLastError() << '\n';
            continue;
        } else if (num_bytes == 0) {
            std::cout << "Client disconnected\n";
            continue;
        }
        Request request = parse_request(msg);
        write_log(request, num_bytes);
        if (request.method == "GET") handle_GET(request, config, new_socket); 
        closesocket(new_socket);
    }
    
        

    WSACleanup();
    closesocket(serversocket);
    return 0;
}