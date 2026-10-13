#include <string>
#include <winsock2.h>

SOCKET accept_connection(SOCKET server_socket);
int recieve_request(SOCKET new_socket, std::string& msg);