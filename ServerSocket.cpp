#include "ServerSocket.hpp"

ServerSocket::ServerSocket(int port) {
  Socket::create();
  Socket::bind(port);
  Socket::listen();
}

ServerSocket::~ServerSocket() {
}

const ServerSocket &ServerSocket::operator<<(std::string const &mes) const {
  Socket::send(mes);
  return (*this);
}

const ServerSocket &ServerSocket::operator>>(std::string &mes) const {
  Socket::recv(mes);
  return (*this);
}

void ServerSocket::accept(ServerSocket &new_server_socket) {
  Socket::accept(new_server_socket);
}
