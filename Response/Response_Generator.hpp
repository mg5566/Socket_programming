#ifndef RESPONSE_GENERATOR_HPP
#define RESPONSE_GENERATOR_HPP

#include <map>
#include <string>

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
    void set_header(std::string &res_msg);

    // std::string get_res_msg(void);
};

#endif