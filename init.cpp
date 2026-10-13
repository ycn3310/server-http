#include <winsock.h>

SOCKADDR_IN init_service(int family, int port, u_long address){
    SOCKADDR_IN service{};
    service.sin_family = family;
    service.sin_port = htons(port);
    service.sin_addr.s_addr = address;
    return service;
}

int init_WSA(WSADATA *wsaData){
    WORD WordVersion = MAKEWORD(2, 2);
    return WSAStartup(WordVersion, wsaData);
}