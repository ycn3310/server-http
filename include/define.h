#pragma once

#include <string>

struct Request
{
    std::string method;
    std::string path;
    std::string version;
};

struct Config
{
    int port;
    std::string root_path;
    std::string index_file;
};

#define BUFFER_SIZE 1024
#define MSG_SIZE 1024
#define MAX_CLIENTS 10