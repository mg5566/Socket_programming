#ifndef REQUEST_PARSE_HPP
#define REQUEST_PARSE_HPP

#include "Request_Message.hpp"
#include <vector>

class Request_Parse {
 private:
  //std::vector<std::string> message_vector;
  std::string origin_message;
  Request_Message requeset_message;

 public:
  Request_Parse();
  Request_Parse(std::string buffer);
  ~Request_Parse();

  void run_parsing(void);
  std::vector<std::string> parse_message(std::string message);
  void parse_start_line(std::string message);
  void parse_header(std::string message);
  void parse_entity(std::string message);
};
#endif
