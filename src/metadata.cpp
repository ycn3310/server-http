#include <string>
#include <winsock2.h>
#include <unordered_map>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>

#include "../include/define.h"

const char* weekdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

const char* months[] = {
    "Jan","Feb","Mar","Apr","May","Jun",
    "Jul","Aug","Sep","Oct","Nov","Dec"
};

std::string  MIME_type(std::string filename){
    size_t pos = filename.find_last_of('.');
    if(pos != std::string::npos && pos != filename.length() - 1){
        size_t slash_pos = filename.find_last_of("/\\");
        if (slash_pos == std::string::npos || pos > slash_pos) {
            std::string ext = filename.substr(pos);
            std::unordered_map<std::string, std::string> MIME_types = {
                {".html", "text/html"},
                {".css", "text/css"},
                {".js",   "application/javascript"},
                {".png",  "image/png"},
                {".jpeg", "image/jpeg"},
                {".jpg",  "image/jpeg"},
                {".scss", "text/x-scss"},
                {".svg", "image/svg+xml"},
                {".ico", "image/vnd.microsoft.icon"}
            };
            //searching for the MIME type based on the extension
            auto it = MIME_types.find(ext);
            //if the extension is found we return the second member
            if(it != MIME_types.end()){
                return it->second;
            }
        }
    }
    return "application/octet-stream";
}

long size_of_file(FILE *file){
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    return fileSize;
}

std::string get_HTTP_time(){
    time_t timestamp = time(&timestamp);
    std::tm tm = *gmtime(&timestamp);
    std::ostringstream date;

    date
        << weekdays[tm.tm_wday] << ", "
        << std::setw(2) << std::setfill('0') << tm.tm_mday << ' '
        << months[tm.tm_mon] << ' '
        << tm.tm_year + 1900 << ' '
        << std::setw(2) << tm.tm_hour << ':'
        << std::setw(2) << tm.tm_min << ':'
        << std::setw(2) << tm.tm_sec
        << " GMT";

    return date.str();
}




#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

Config load_config(std::string path){
    Config config;
    std::ifstream file(path);
    std::string keyword;

    file >> keyword >> config.port;           // fine: a number has no spaces

    file >> keyword >> std::ws;               // skip spaces after the keyword
    std::getline(file, config.root_path);     // take the whole rest of the line

    file >> keyword >> std::ws;
    std::getline(file, config.index_file);

    // optional: handle CRLF files
    for (std::string* s : {&config.root_path, &config.index_file})
        if (!s->empty() && s->back() == '\r') s->pop_back();

    return config;
}


