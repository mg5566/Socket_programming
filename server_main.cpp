#include "ServerSocket.hpp"

int main(void) {
  ServerSocket server(12345);

  ServerSocket server_socket;
  server.accept(server_socket);

  while (1) {
    std::string mes;
    server_socket >> mes;
    server_socket << mes;
  }
  return (0);
}
