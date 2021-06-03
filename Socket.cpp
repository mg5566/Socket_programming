#include "Socket.hpp"

Socket::Socket() : m_socket(-1){
  memset(&m_addr, 0, sizeof(m_addr));
}

Socket::~Socket() {
  if (is_valid())
    close(m_socket);
}

bool Socket::create() {
  m_socket = socket(AF_INET, SOCK_STREAM, 0);

  if (!is_valid())
    return (false);

  // socket for reusing
  int on = 1;
  if ( setsockopt ( m_socket, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
    return false;

  // SET NON-BLOCKING
  fcntl(m_socket, F_SETFL, O_NONBLOCK);

  return (true);
}