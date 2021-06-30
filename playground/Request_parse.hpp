#ifndef REQUEST_PARSE_HPP
#define REQUEST_PARSE_HPP

#include <string>
#include <vector>
#include <map>

class Request_Parse {
 private:
  //std::vector<std::string> message_vector;
  std::string origin_message;
  // return 에 사용됨
  std::map<std::string, std::string> start_line_map;
  // 3 개밖에 안되니까 각각 나누는 방식을 고려해봅니다.
  std::map<std::string, std::vector<std::string> > header_map;
  std::string entity_str;

  Request_Parse(std::string buffer);
 public:
  Request_Parse();
  ~Request_Parse();

  void run_parsing(void);
  std::vector<std::string> split_message(std::string message);
  void parse_start_line(std::string message);
  void parse_header(std::string message);
  void parse_entity(std::string message);

  // 향후 getter 가 필요하다고 판된됩니다.
  void set_message(std::string const &buffer);

  std::map<std::string, std::string> get_start_line_map();
  // 각각 나눠서 담고있다면 getter 도 각각 만들어야합니다.
  std::map<std::string, std::vector<std::string> > get_header_map();
  std::string get_entity_str();

};

std::vector<std::string> split(std::string str, char limiter);
std::vector<std::string> split_value(std::string header, std::string str);

void print_parsed_data(std::map<std::string, std::string> sl, std::map<std::string, std::vector<std::string> > h, std::string e);

#endif
