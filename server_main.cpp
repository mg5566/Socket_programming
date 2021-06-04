/*
#include <sys/socket.h>  // socket
#include <netinet/in.h>  // sockaddr_in
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
*/

#include "Socket.hpp"

#define PORT 123456

int main(void) {
  Socket socket;
  Socket new_socket;

  socket.create();
  socket.bind(PORT);
  socket.listen();
  while (1) {
    socket.accept(new_socket);
    new_socket.send("fuck you");

    std::string mes;
    int recv_len = new_socket.recv(mes);
    while (recv_len > 0) {
      std::cout << "From Client : " << mes << std::endl;
      recv_len = new_socket.recv(mes);
    }
  }

  return (0);
}
