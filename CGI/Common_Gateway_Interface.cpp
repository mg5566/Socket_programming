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
  envp[idx] = memcpy(temp, key.c_str());
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
  if (!(envp = (char **)malloc(sizeof(char *) * 14)))
    return ;
  // set_env(envp, 0, parsed_request_data.get_header[]);
  set_env(envp, 0, "AUTH_TYPE", parsed_request_data.get_header["Authorization"][0]);  // basic
  set_env(envp, 1, "CONTENT_LENGTH", parsed_request_data.get_header["Content-Length"]);
  set_env(envp, 2, "CONTENT_TYPE", parsed_request_data.get_header["Content-Type"]);
  set_env(envp, 3, "GATEWAY_INTERFACE", "PHP/8.0");  // $ php-cgi -v 를 참고했습니다.
  set_env(envp, 4, "PATH_INFO", "php-cgi");  // 경로를 "/path/php-cgi" 이렇게 설정하면 되는 것 같습니다.
  set_env(envp, 5, "PATH_TRANSLATED", "aaaa");  // 뭔지 감이 1도 안옴...
  // https://datatracker.ietf.org/doc/html/rfc3875#page-13 를 참고해봅시다.
  set_evn(envp, 6, "QUERY_STRING", "aaaa");  // URL 에서 parsing 을 해야겠군요...
  set_env(envp, 7, "REMOTE_ADDR", parsed_request_data.get_header["Host"]);  // 지금 127.0.0.1:<PORT> 가 나올텐데, <PORT> 를 제거해야할지도?!
  set_env(envp, 8, "REMOTE_IDENT", parsed_request_data.get_header[""]);
  set_env(envp, 0, "REQUEST_METHOD", parsed_request_data.get_heaher["Method"]);
}
