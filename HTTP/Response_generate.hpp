#ifndef RESPONSE_GENERATE_HPP
#define RESPONSE_GENERATE_HPP

#include <string>
#include <vector>
#include <map>

class Response_Generate {
  private:
    std::string response_message;
    // write(client_fd, Response_message.c_str(), message.size());

  public:
    Response_Generate();
    ~Response_Generate();

    void gerenate_response_message(void);
    void gen_start_line(void);
    void gen_header(void);
    void gen_entity(void);
};

#endif
