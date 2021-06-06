/*
#include <sys/socket.h>  // socket
#include <netinet/in.h>  // sockaddr_in
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
*/

#include <sys/select.h>  // select FD_SET FD_CLR...
#include "Socket.hpp"

#define PORT 1234

int main(void) {
  Socket socket;
  Socket client_socket;
  /*
  fd_set reads;
  struct timeval timeout;
  int result;  // result for select
  */

  socket.create();
  socket.bind(PORT);
  socket.listen();
  /*
  // set READ FILE DESCRIPTOR
  FD_ZERO(&reads);
  // set timeout for select
  timeout.tv_sec = 3;
  timeout.tv_usec = 0;
  */

  while (1) {
    std::cout << "Waitting for fucking connections....." << std::endl;
    socket.accept(client_socket);
    client_socket.send("fucking client!!! fuck you!!!!!");

    std::string mes;
    mes.clear();
    int recv_len = client_socket.recv(mes);
    while (recv_len > 0) {
      //std::cout << "From Client : " << mes << std::endl;
      std::cout << "From Client : " << mes;
      mes.clear();
      recv_len = client_socket.recv(mes);
    }
    /*
    FD_SET(client_socket.m_socket, &reads);
    result = select(3, &reads, 0, 0, &timeout);
    if (result < 0) {
      std::cout << "Error : select error" << std::endl;
      exit(-1);
    } else if (result == 0) {
      std::cout << "timeout!!! there are not message from fucking client" << std::endl;
    } else {
      std::string mes;
      int recv_len = client_socket.recv(mes);
      while (recv_len > 0) {
        std::cout << "From Client : " << mes << std::endl;
        recv_len = client_socket.recv(mes);
      }
    }
    */
  }

  return (0);
}
