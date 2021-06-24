#include "Request_parse.hpp"

#include <iostream>

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
  for (std::vector<std::string>::iterator it = message_vector.begin(); it != message_vector.end(); ++it)
    std::cout << "test : " << *it << std::endl;
  parse_start_line(message_vector[0]);
  parse_header(message_vector[1]);
  parse_entity(message_vector[2]);
}

/*
편한 parsing 을 위해서 메세지를 start-line, header, entity 로 분리합니다.
split 된 message 는 vector 로 관리합니다.
*/
std::vector<std::string> Request_Parse::split_message(std::string message) {
  std::vector<std::string> temp;

  // find 후 substr 을 사용하여 request message 를 split 합니다.
  // erase 를 사용하지 않았지만 sequence erase 를 사용하여 지우고 다시 find 하는 방법도 있습니다.
  std::size_t line_end_pos = message.find("\r\n");
  std::size_t head_end_pos = message.find("\r\n\r\n");
  //std::cout << "line_end_pos : " << line_end_pos << std::endl;
  //std::cout << "head_end_pos : " << head_end_pos << std::endl;
  temp.push_back(message.substr(0, line_end_pos));
  // line_end_pos 에 +2 를 해야 \r\n(start line 과 head 의 구분문자열) 을 피할 수 있습니다.
  temp.push_back(message.substr(line_end_pos + 2, head_end_pos));
  //std::cout << "entity_end_pos : " << message.length() << std::endl;
  // head_end_pos 에 +4 를 해야 \r\n\r\n(head 와 entity 의 구분문자열) 을 피할 수 있습니다.
  temp.push_back(message.substr(head_end_pos + 4, message.length()));
  /*
  std::cout << "line_end_pos : " << line_end_pos << std::endl;
  std::cout << "head_end_pos : " << head_end_pos << std::endl;
  std::cout << "test line_end_pos" << std::endl;
  std::cout << message.substr(0, line_end_pos) << std::endl;
  std::cout << "finish line_end_post" << std::endl;
  // 왜인지 모르겠지만 출력이 안되고 있습니다.
  std::cout << "test head_end_pos" << std::endl;
  std::cout << message.substr(line_end_pos + 1, head_end_pos) << std::endl;
  std::cout << "finish head_end_pos" << std::endl;
  */
  return (temp);
}

/*
split 된 message 를 parsing 합니다.
*/
void Request_Parse::parse_start_line(std::string message) {
  // parsing 된 data 는 member variable start_line_map 에 key(string), value(string) 형식으로 저장합니다.
  // find 로 space 를 찾고 method 를 저장한다음 method + space 를 지우고 다음을 parsing 합니다.
}

void Request_Parse::parse_header(std::string message) {
  (void)message;
}

void Request_Parse::parse_entity(std::string message) {
  (void)message;
}
