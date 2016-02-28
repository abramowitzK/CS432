#ifndef STRING_UTIL
#define STRING_UTIL
#include <vector>
#include <string>
#include <sstream>
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> splitLine(const std::string &s, char delim) ;


#endif