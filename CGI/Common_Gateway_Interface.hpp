#ifndef COMMON_GATEWAY_INTERFACE_HPP
#define COMMON_GATEWAY_INTERFACE_HPP

#include "Request_Message.hpp"

#include <string>

class CGI {
  private:
    Request_Message parsed_request_data;

    char **envp;
    char **argv;
    // std::string entity_body;
    // fork | pipe | execve | buf 에 필요한 variables
    int bytes;
    int pipe_fd[2];
    pid_t pid;
    // result
    std::string result;

  public:
    CGI();
    ~CGI();

/*
    // set entity_body
    void set_entity_body(std::string body);
*/

    // set request message
    void set_request_message(Request_Message *data);

    // 환경변수 관련 함수
    void set_env(char **envp, int idx, std::string key, std::string value);
    void create_envp();
    char **get_env();

    // path 관련 함수
    void create_argv();
    char **get_argv();

    // execve 관련 함수
    void excute_CGI();

    // test print 함수
    void test_print();

};

#endif
