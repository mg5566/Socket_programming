#include "Response_Message.hpp"

void Response_Message::clear() {
    // start line
    version.clear();
    status_code = 0;
    status_text.clear();
    // Response header
    allow.clear();
    content_location.clear();
    last_modified.clear();
    location.clear();
    retry_after.clear();
    server.clear();
    transfer_encoding.clear();
    www_authenticate.clear();
    // Entity header
    content_language.clear();
    content_length.clear();
    content_type.clear();
    // Entity body
    entity.clear();

    /* another design
    response_map.clear();
    status_code = 0;
    */
}
