#ifndef REQUEST_PARSE_HPP
#define REQUEST_PARSE_HPP

#include <string>
#include <vector>
#include <map>

class Request_Parse {
 private:
  //std::vector<std::string> message_vector;
  std::string origin_message;
  //Request_Message requeset_message;
  std::map<std::string, std::string> request_message_map;

 public:
  Request_Parse();
  Request_Parse(std::string buffer);
  ~Request_Parse();

  void run_parsing(void);
  std::vector<std::string> split_message(std::string message);
  void parse_start_line(std::string message);
  void parse_header(std::string message);
  void parse_entity(std::string message);

  // 향후 getter 가 필요하다고 판된됩니다.
};
#endif
