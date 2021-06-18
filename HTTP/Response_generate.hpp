#ifndef RESPONSE_GENERATE_HPP
#define RESPONSE_GENERATE_HPP

#include <string>
#include <vector>
#include <map>

class Response_Generate {
  private:
    std::string response_message;

  public:
    void gerenate_response_message(void);
    void gen_start_line(void);
    void gen_header(void);
    void gen_entity(void);
};

#endif
