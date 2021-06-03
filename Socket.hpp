#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>  // socket
#include <netinet/in.h>  // sockaddr_in

class Socket {
  private:
    int m_socket;
    sockaddr_in m_addr;
  public:
    Socket();
    virtual ~Socket();

    // Server
    bool create();

    // util
    bool is_valid() const { return (!m_socket != -1); }

};

#endif