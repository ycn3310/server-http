#include <iostream>
#include <fstream>
#include <ctime>

#include "../include/metadata.h"
#include "../include/define.h"


void write_log(Request request, int num_bytes){
    std::ofstream log_file("server.log", std::ios::app);
    if(!log_file.is_open()){
        std::cerr << "couldn't open log file" << std::endl;
        return;
    }

    time_t timestamp = time(&timestamp);
    std::tm tm = *gmtime(&timestamp);

    #if defined(_WIN32)
        gmtime_s(&tm, &timestamp); 
    #else
        gmtime_r(&timestamp, &tm); 
    #endif

    log_file << "[ " << tm.tm_mday << "/" << tm.tm_mon+1 <<  "/" << tm.tm_year+1900 << 
    " | " << tm.tm_hour << ":" << tm.tm_min << ":" << tm.tm_sec << " ] ";

    log_file << request.method << ' ' << request.path << ' ' << request.version << " bytes: " << num_bytes << '\n';

}