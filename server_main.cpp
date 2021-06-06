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
#define BACK_LOG 10


int setup_server(int port, int back_log) {
  /*
  Socket socket;

  socket.create();
  socket.bind(port);
  socket.listen(back_log);
  return (socket.m_socket);
  */
  int server;

  server = socket(AF_INET, SOCK_STREAM, 0);
  // socket for reusing
  int on = 1;
  if ( setsockopt (server, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
    return false;



}

int accept_new_connection(int server_fd) {
  int client;
  sockaddr_in addr;
  int addr_size;

  if (client = accept(server_fd, (sockaddr *)&addr, (socklen_t *)&addr_size) < 0)
    return (false);

  return (client);
}


int main(void) {
  /*
  Socket socket;
  Socket client_socket;
  */
  /*
  fd_set reads;
  struct timeval timeout;
  int result;  // result for select
  */

  // 이 부분도 이쁘게 만들 수 있을것만 같단 말이지...
  int server_fd = setup_server(PORT, BACK_LOG);
  /*
  socket.create();
  socket.bind(PORT);
  //socket.listen();
  socket.listen(10);
  */

  /*
  // set READ FILE DESCRIPTOR
  FD_ZERO(&reads);
  // set timeout for select
  timeout.tv_sec = 3;
  timeout.tv_usec = 0;
  */

  while (1) {
    // 이 부분을 더 이쁘게 만들 수 있을것만 같은 느낌적인 느낌이 드는데....
    std::cout << "Waitting for fucking connections....." << std::endl;
    int client_fd = accept_new_connection(server_fd);

    /*
    socket.accept(client_socket);
    client_socket.send("fucking client!!! fuck you!!!!!");
    */

   /*
    std::string mes;
    mes.clear();
    int recv_len = client_socket.recv(mes);
    while (recv_len > 0) {
      //std::cout << "From Client : " << mes << std::endl;
      std::cout << "From Client : " << mes;
      mes.clear();
      recv_len = client_socket.recv(mes);
    }
    */

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
