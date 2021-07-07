#ifndef RESPONSE_GENERATOR_HPP
#define RESPONSE_GENERATOR_HPP

#include <map>
#include <string>
#include <vector>
#include <fstream>

#define SPACE " "
#define CRLF "\r\n"

class Response_Generator {
  private:
    std::map<int, std::string> status_map;
    // std::string res_msg;  // 완성된 Response_Message

  public:
    Response_Generator();
    ~Response_Generator();
    
    void set_start_line(std::string &res_msg);
    void set_headers(std::string &res_msg, std::map<std::string, std::vector<std::string> > header_map);
    void set_entity_body(std::string &res_msg, std::string file_name);

    // std::string get_res_msg(void);
    std::string gen_header(std::string key, std::vector<std::string> values);
};

#endif