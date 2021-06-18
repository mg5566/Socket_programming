#include "Request_Message.hpp"

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
