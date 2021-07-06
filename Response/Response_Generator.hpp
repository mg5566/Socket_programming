#ifndef RESPONSE_GENERATOR_HPP
#define RESPONSE_HENERATOR_HPP

#include <map>
#include <string>

class Response_Generator {
  private:
    std::map<int, std::string> status_map;
    std::string res_msg;  // 완성된 Response_Message

  public:
    Response_Generator();
    ~Response_Generator();
    
    void set_status_map(void);
    std::string get_res_msg(void);
};

#endif