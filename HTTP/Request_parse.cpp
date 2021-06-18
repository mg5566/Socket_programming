#include "Request_parse.hpp"

Request_Parse::Request_Parse() : origin_message(NULL) {
}

Request_Parse::Request_Parse(std::string buffer) : origin_message(buffer) {
}

// alloc 을 하지않아서 free 할 것이 없습니다.
Request_Parse::~Request_Parse() {
}

void Request_Parse::run_parsing(void) {
  std::vector<std::string> message_vector;

  message_vector = split_message(origin_message);
  parse_start_line(message_vector[0]);
  parse_header(message_vector[1]);
  parse_entity(message_vector[2]);
}

/*
편한 parsing 을 위해서 메세지를 start-line, header, entity 로 분리합니다.
split 된 message 는 vector 로 관리합니다.
*/
std::vector<std::string> Request_Parse::split_message(std::string message) {
}

/*
split 된 message 를 parsing 합니다.
*/
void parse_start_line(std::string message) {
}

void parse_header(std::string message) {
}

void parse_entity(std::string message) {
}
