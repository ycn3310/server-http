#include <winsock.h>

SOCKADDR_IN init_service(int family, int port, u_long address);
int init_WSA(WSADATA *wsaData);