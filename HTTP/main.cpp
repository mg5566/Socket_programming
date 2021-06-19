#include <iostream>
#include <string>

#include "Request_parse.hpp"

int main(void) {
    std::string buffer;

    buffer += "POST /cgi-bin/process.cgi HTTP/1.1\r\n";
    buffer += "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n";
    buffer += "Host: www.tutorialspoint.com\r\n";
    buffer += "Content-Type: text/xml; charset=utf-8\r\n";
    buffer += "Content-Length: length\r\n";
    buffer += "Accept-Language: en-us\r\n";
    buffer += "Accept-Encoding: gzip, deflate\r\n";
    buffer += "Connection: Keep-Alive\r\n";
    buffer += "\r\n";
    buffer += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    buffer += "<string xmlns=\"http://clearforest.com/\">string</string>";

    std::cout << "test print buffer" << std::endl;
    std::cout << buffer << std::endl;

    Request_Parse parser(buffer);

    return (0);
}