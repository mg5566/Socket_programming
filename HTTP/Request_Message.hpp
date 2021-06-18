#ifndef REQUEST_MESSAGE_HPP
#define REQUEST_MESSAGE_HPP

#include <string>
#include <map>

class Request_Message {
  private:
    // start line
    std::string method;
    std::string url;
    std::string version;
    // Header
    /* Request header
    Accept-Charset
    Accept-Language
    Authorization
    Host
    Referer
    User-Agent
    */
    std::map<std::string, std::string> accept_charset;
    std::map<std::string, std::string> accept_language;
    std::map<std::string, std::string> authorization;
    std::map<std::string, std::string> host;
    std::map<std::string, std::string> referer;
    std::map<std::string, std::string> user_agent;
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

    /* another design
    std::map<std::string, std::string> request_map;
    */

  public:
    Request_Message();
    Request_Message(const Request_Message &rhs);
    ~Request_Message();
    Request_Message &operator=(const Request_Message &rhs);
    /* getter setter
    Request Message 작성에 필요한 기능
    */
    // start line
    const std::string getMethod(void) const;
    const std::string getUrl(void) const;
    const std::string getVersion(void) const;
    void setMethod(const std::string new_method);
    void setUrl(const std::string new_url);
    void setVersion(const std::string new_version);
    // Header
    const std::map<std::string, std::string> getAccept_charset(void) const;
    const std::map<std::string, std::string> getAccept_language(void) const;
    const std::map<std::string, std::string> getAuthorization(void) const;
    const std::map<std::string, std::string> getHost(void) const;
    const std::map<std::string, std::string> getReferer(void) const;
    const std::map<std::string, std::string> getUser_agent(void) const;
    void setAccept_charset(const std::string new_accept_charset);
    void setAccept_language(const std::string new_accept_language);
    void setAuthorization(const std::string new_authorization);
    void setHost(const std::string new_host);
    void setReferer(const std::string new_referer);
    void setUser_agent(const std::string new_user_agent);
    const std::map<std::string, std::string> getContent_language(void) const;
    const std::map<std::string, std::string> getContent_length(void) const;
    const std::map<std::string, std::string> getContent_type(void) const;
    void setContent_language(const std::string new_content_language);
    void setContent_length(const std::string new_content_length);
    void setContent_type(const std::string new_content_type);
    // Entity
    const std::map<std::string, std::string> getEntity(void) const;
    void setEntity(std::string new_entity) const;

    /* clear
    멤버 변수들의 값을 초기화합니다.
    */
    void clear(void);
};

#endif
