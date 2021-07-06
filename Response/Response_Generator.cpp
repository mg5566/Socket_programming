#include "Response_Generator.hpp"

Response_Generator::Response_Generator() {}

Response_Generator::~Response_Generator() {}

void Response_Generator::set_start_line(std::string &res_msg) {
    res_msg += "HTTP/1.1";
    res_msg += SPACE;
    res_msg += std::to_string(403);
    res_msg += SPACE;
    res_msg += "Forbidden";
    res_msg += CRLF;
}

void Response_Generator::set_header(std::string &res_msg) {
    res_msg += "Server";
    res_msg += SPACE;
    res_msg += ":";
    res_msg += SPACE;
    res_msg += "nginx"; 
}