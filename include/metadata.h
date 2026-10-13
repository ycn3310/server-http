#include <string>
#include <sstream>
#include "define.h"

std::string  MIME_type(std::string filename);
long size_of_file(FILE *file);
std::string get_HTTP_time();
Config load_config(std::string path);