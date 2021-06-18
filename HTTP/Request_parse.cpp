#include "Request_parse.hpp"

Request_Parse::Request_Parse() : origin_message(NULL) {
}

Request_Parse::Request_Parse(std::string buffer) : origin_message(buffer) {
}

Request_Parse::~Request_Parse() {

}

void Request_Parse::run_parsing(void) {
  std::vector<std::string> message_vector;

  message_vector = parse_message(origin_message);
  parse_start_line(message_vector[0]);
  parse_header(message_vector[1]);
  parse_entity(message_vector[2]);
}

std::vector<std::string> Request_Parse::parse_message(std::string message) {
}

void parse_start_line(std::string message) {
}

void parse_header(std::string message) {
}

void parse_entity(std::string message) {
}
