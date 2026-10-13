#include <string>
#include <winsock2.h>

#include "../include/define.h"
#include "../include/metadata.h"

void send_200(SOCKET new_socket, long fileSize, std::string content_type){
    std::string response =  
    "HTTP/1.1 200 OK\r\n"
    "Date:" + get_HTTP_time() + " \r\n"
    "Server: YacineHomeMadeServer\r\n"
    "Content-type:" + content_type + "\r\n"
    "Content-Length: " + std::to_string(fileSize) + "\r\n"
    "\r\n";
    send(new_socket, response.c_str(), response.length(), 0);
}

void send_404(SOCKET new_socket){ 
    std::string response = 
    "HTTP/1.1 404 Not Found\r\n"
    "Date:" + get_HTTP_time() + " \r\n"
    "Server: YacineHomeMadeServer\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: 18916\r\n"
    "\r\n";
    
    send(new_socket, response.c_str(), response.length(), 0);
}

void send_response_file(SOCKET new_socket, FILE* response_file){
    char buffer[BUFFER_SIZE];
    size_t bytesread;
    while((bytesread = fread(buffer, 1, sizeof(buffer),response_file)) >0){
        send(new_socket, buffer, bytesread ,0);
    }
    fclose(response_file);
}