#ifndef SERVER_SOCKET_HPP
#define SERVER_SOCKET_HPP

#include "Socket.hpp"

#include <iostream>

class ServerSocket : public Socket {
  public:
    ServerSocket() {}
    ServerSocket(int port);
    virtual ~ServerSocket();

    const ServerSocket &operator<<(std::string const &mes) const;
    const ServerSocket &operator>>(std::string &mes) const;

    void accept(ServerSocket &new_server_socket);

};

#endif
