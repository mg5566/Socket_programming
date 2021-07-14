#include "Common_Gateway_Interface.hpp"

CGI() {}

~CGI() {}

/*
void CGI::set_entity_body(std::string &body) {
  entity_body = body;
}
*/

void CGI::set_request_message(Request_Message *data) {
  parsed_request_data = *data;
}

void CGI::set_env(char **envp, int idx, std::string key, std::string value) {
  char *temp;

  key += "=";
  key += value;
  envp[idx] = strcpy(temp, key.c_str());
}

/*
AUTH_TYPE
CONTENT_LENGTH
CONTENT_TYPE
GATEWAY_INTERFACE
PATH_INFO
PATH_TRANSLATED
QUERY_STRING
REMOTE_ADDR
REMOTE_IDENT
REMOTE_USER
REQUEST_METHOD
REQUEST_URI
SCRIPT_NAME
SERVER_NAME
SERVER_PORT
SERVER_PROTOCOL
SERVER_SOFTWARE
*/
void CGI::create_envp() {
  if (!(envp = (char **)malloc(sizeof(char *) * 18)))
    return ;
  // set_env(envp, 0, parsed_request_data.get_header[]);
  set_env(envp, 0, "AUTH_TYPE", parsed_request_data.get_header["Authorization"][0]);  // basic
  set_env(envp, 1, "CONTENT_LENGTH", parsed_request_data.get_header["Content-Length"]);
  set_env(envp, 2, "CONTENT_TYPE", parsed_request_data.get_header["Content-Type"]);  // application/x-www-form-urlencoded
  set_env(envp, 3, "GATEWAY_INTERFACE", "PHP/8.0");  // $ php-cgi -v 를 참고했습니다.
  set_env(envp, 4, "PATH_INFO", "php-cgi");  // 경로를 "/path/php-cgi" 이렇게 설정하면 되는 것 같습니다.
  set_env(envp, 5, "PATH_TRANSLATED", "");  // 뭔지 감이 1도 안옴...
  // https://datatracker.ietf.org/doc/html/rfc3875#page-13 를 참고해봅시다.
  // POST method 가 오는 경우 query string 은 entity body 에 오는 걸로 합시다.
  // 그러면 URL 에서 따로 파싱을 할 필요가 없긴합니다.
  set_evn(envp, 6, "QUERY_STRING", parsed_request_data.get_entity_body);// URL 에서 parsing 을 해야겠군요...
  set_env(envp, 7, "REMOTE_ADDR", parsed_request_data.get_header["Host"]);  // 지금 127.0.0.1:<PORT> 가 나올텐데, <PORT> 를 제거해야할지도?!
  set_env(envp, 8, "REMOTE_IDENT", "");  // client 의 host 이름
  set_env(envp, 9, "REMOTE_USER", "");
  set_env(envp, 10, "REQUEST_METHOD", parsed_request_data.get_heaher["Method"]);
  set_env(envp, 11, "REQUEST_URI", "");
  set_env(envp, 12, "SCRIPT_FILENAME", "");
  set_env(envp, 13, "SERVER_NAME", parsed_request_data.get_header["Host"]);
  set_env(envp, 14, "SERVER_PORT", "");
  set_env(envp, 15, "SERVER_PROTOCOL", "HTTP/1.1");
  set_env(envp, 16, "SERVER_SOFTWARE", "");
  envp[17] = NULL;
}

char ** CGI::get_env() {
  return (envp);
}

void CGI::create_argv() {
  if (!(argv = (char **)malloc(sizeof(char *) * 2)))
    return ;
  argv[0] = strcpy(temp, "php-cgi");
  // argv[1] 에 파일을 담곤했는데, 없이도 가능하니 없이 해보겠습니다.
  argv[1] = NULL;
}

char **CGI::get_argv() {
  return (argv);
}

void CGI::excute_CGI() {
  pipe(pipe_fd);
  pid = fork();
  if (pid < 0)
    std::cerr << "fork fail" << std::endl;
  else if (pid == 0) {  // child
    dup2(pipe_fd[1], 1);
    // path 는 config 파일에서 가져온 data 를 활용해야합니다.
    if (execve("/usr/local/bin/php-cgi", argv, envp) == -1)
      std::cerr << "execve fail" << std::endl;
    exit (1);
  } else {
    // 이 부분이 문제인데, 결과값은 결국에 response 에 담아야합니다.
    // 바로 response 에 담을 순 없는 건가?!
    // 바로 담을 수 있으면 어디에 담았다가 전달해줄 필요가 없을 듯 합니다?!
    bytes = read(pipe_fd[0], buf, BUFFER_SIZE);
    result = bytes;

  }
}

void CGI::test_print(int is_result = 1) {
  if (is_result != 1) {
    for (int idx = 0; argv[idx]; ++idx)
      std::cout << "argv[" << idx << "] : " << argv[idx] << std::endl;
    for (int idx = 0; envp[idx]; ++idx)
      std::cout << "argv[" << idx << "] : " << envp[idx] << std::endl;
  } else {
    std::cout << result << std::endl;
  }
}
