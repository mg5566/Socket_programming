#ifndef RESPONSE_MESSAGE_HPP
#define RESPONSE_MESSAGE_HPP

#include <string>
#include <map>

class Response_Message {
  private:
    // start line
    std::string version;
    unsigned int status_code;
    std::string status_text;
    // Header
    /* Response header
    Allow
    Content-Location
    Last-Modified
    Location
    Retry-After
    Server
    Transfer-Encoding
    WWW-Authenticate
    */
    std::map<std::string, std::string> allow;
    std::map<std::string, std::string> content_location;
    std::map<std::string, std::string> last_modified;
    std::map<std::string, std::string> location;
    std::map<std::string, std::string> retry_after;
    std::map<std::string, std::string> server;
    std::map<std::string, std::string> transfer_encoding;
    std::map<std::string, std::string> www_authenticate;
    /* Entity header
    Content-Language
    Content-Length
    Content-Type
    */
    std::map<std::string, std::string> content_language;
    std::map<std::string, std::string> content_length;
    std::map<std::string, std::string> content_type;
    // Entity body
    std::string entity;

  public:
    /* getter setter
    Response Message 에 필요한 기능
    */
    // Header
    const std::string getVersion(void) const;
    const unsigned int getStatus_code(void) const;
    const std::string getStatus_text(void) const;
    void setVersion(std::string new_version);
    void setStatus_code(unsigned int new_status_code);
    void setStatus_text(std::string new_status_text);
    // Header
    const std::map<std::string, std::string> getAllow(void) const;
    const std::map<std::string, std::string> getContent_location(void) const;
    const std::map<std::string, std::string> getLast_modified(void) const;
    const std::map<std::string, std::string> getLocation(void) const;
    const std::map<std::string, std::string> getRetry_after(void) const;
    const std::map<std::string, std::string> getServer(void) const;
    const std::map<std::string, std::string> getTransfer_encoding(void) const;
    const std::map<std::string, std::string> getWWW_authenticate(void) const;
    void setAllow(std::string new_allow);
    void setContent_location(std::string new_content_location);
    void setLast_modified(std::string new_last_modified);
    void setLocation(std::string new_location);
    void setRetry_after(std::string new_retry_after);
    void setServer(std::string new_server);
    void setTransfer_encoding(std::string new_transfer_encoding);
    void setWWW_authenticate(std::string new_www_authenticate);
    const std::map<std::string, std::string> getContent_language(void) const;
    const std::map<std::string, std::string> getContent_length(void) const;
    const std::map<std::string, std::string> getContent_type(void) const;
    void setContent_language(std::string new_content_language);
    void setContent_length(std::string new_content_length);
    void setContent_type(std::string new_content_type);

};
#endif