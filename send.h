#include <string>
#include <winsock2.h>

void send_200(SOCKET new_socket, long fileSize, std::string content_type);
void send_404(SOCKET new_socket);
void send_response_file(SOCKET new_socket, FILE* response_file);