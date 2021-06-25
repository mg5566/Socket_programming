#ifndef REQUEST_PARSE_HPP
#define REQUEST_PARSE_HPP

#include <string>
#include <vector>
#include <map>

class Request_Parse {
 private:
  //std::vector<std::string> message_vector;
  std::string origin_message;
  std::map<std::string, std::string> start_line_map;
  std::map<std::string, std::vector<std::string> > header_map;
  std::string entity_str;

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

std::vector<std::string> split(std::string str, char limiter);
std::vector<std::string> split_value(std::string header, std::string str);

#endif
