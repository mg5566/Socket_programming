#include "Request_Message.hpp"

Request_Message::Request_Message() {
}

Request_Message::Request_Message(const Request_Message &rhs) {
}

Request_Message::~Request_Message() {
  clear();
}

Request_Message &Request_Message::operator=(const Request_Message &rhs) {
  // start line
  setMethod(rhs.getMethod());
  setUrl(rhs.getUrl());
  setVersion(rhs.getVersion());
  // header
  // 이건 좀 더 생각을 해봐야합니다.
  return (*this);
}

void Request_Message::clear(void) {
    // start line
    method.clear();
    url.clear();
    version.clear();
    // header
    accept_charset.clear();
    accept_language.clear();
    authorization.clear();
    host.clear();
    referer.clear();
    user_agent.clear();
    // Entity header
    content_language.clear();
    content_length.clear();
    content_type.clear();
    // Entity body
    entity.clear();

    /* another design
    request_map.clear();
    */
}
