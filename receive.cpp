#include <string>
#include <winsock2.h>
#include <iostream>

#include "define.h"

SOCKET accept_connection(SOCKET server_socket){
    SOCKET new_socket = accept(server_socket, NULL, NULL);
    if(new_socket == INVALID_SOCKET){
        std::cout << "accept() failed | "  << WSAGetLastError() << std::endl;
    } 
    return new_socket;
}

int recieve_request(SOCKET new_socket, std::string& msg){
    msg.clear();
    msg.resize(MSG_SIZE);
    int bytes_received = recv(new_socket, &msg[0], MSG_SIZE, 0);

    if(bytes_received>0){
        msg.resize(bytes_received);
    } else {
        msg.clear();
    }
    return bytes_received;
}