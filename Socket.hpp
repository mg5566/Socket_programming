#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>  // socket
#include <netinet/in.h>  // sockaddr_in

#define MAX_BUFFER_SIZE 1024
//#define MAX_CONNECTOR 10
//#define MAX_CONNECTOR 1

class Socket {
  private:
    sockaddr_in m_addr;
  public:
    int m_socket;
    Socket();
    virtual ~Socket();

    // Server
    bool create();
    bool bind(const int port);
    // server_backlog 가 맞는지 확인이 더 필요합니다.
    bool listen(const int server_backlog) const;

    // Client initialzation
    bool accept(Socket &new_socket) const;

    // Data Transmission
    bool send(const std::string mes) const;
    int recv(std::string &mes) const;

    // util
    bool is_valid() const { return (m_socket != -1); }

};

#endif
