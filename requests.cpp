#include <string>
#include <winsock2.h>
#include <winsock.h>


#include "metadata.h"
#include "define.h"
#include "send.h"

Request parse_request(std::string request_msg){
    Request request;
    std::istringstream request_stream(request_msg);
    request_stream >> request.method >> request.path >> request.version;
    return request;
}

void handle_GET(Request request, Config config, SOCKET new_socket){
    std::string filename = (request.path == "/") ? config.root_path + "\\index.html" : config.root_path + request.path;
    FILE *response_file = fopen(filename.c_str(), "rb");

    if(response_file == nullptr){
        send_404(new_socket);
        response_file = fopen("404.html", "rb");
    } else {
        send_200(new_socket, size_of_file(response_file), MIME_type(filename));
    }
    
    send_response_file(new_socket, response_file);
}