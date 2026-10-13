#include "define.h"
#include <winsock.h>
#include <string>

Request parse_request(std::string request_msg);
void handle_GET(Request request, Config config, SOCKET new_socket);