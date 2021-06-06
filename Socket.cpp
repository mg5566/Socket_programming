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

/*
  // SET NON-BLOCKING
  fcntl(m_socket, F_SETFL, O_NONBLOCK);
*/
  return (true);
}

bool Socket::bind(const int port) {
  if (!is_valid())
    return (false);

  m_addr.sin_family = AF_INET;
  m_addr.sin_addr.s_addr = INADDR_ANY;
  m_addr.sin_port = htons(port);

  int bind_return;

  bind_return = ::bind(m_socket, (struct sockaddr *)&m_addr, sizeof(struct sockaddr));
  if (bind_return == -1)
    return (false);
  return (true);
}

bool Socket::listen() const {
  if (!is_valid())
    return (false);

  int listen_result;

  // Socket file descriptor | max connetor
  // 향후 nginx configuration 을 보고 수정이 필요할듯?!
  listen_result = ::listen(m_socket, MAX_CONNECTOR);

  if (listen_result == -1)
    return (false);
  return (true);
}

bool Socket::accept(Socket &new_socket) const {
  int addr_len = 0;
  std::cout << "test addr_len : " << addr_len << std::endl;
  // client 의 socket fd 를 받아옵니다.
  new_socket.m_socket = ::accept(m_socket, (sockaddr *)&m_addr, (socklen_t *)&addr_len);
  std::cout << "test addr_len : " << addr_len << std::endl;

  if (new_socket.m_socket == -1)
    return (false);
  return (true);
}

bool Socket::send(const std::string mes) const {
  int status = ::send(m_socket, mes.data(), mes.size(), 0);
  if (status == -1)
    return (false);
  return (true);
}

int Socket::recv(std::string &mes) const {
  char buffer[MAX_BUFFER_SIZE + 1];
  memset(&buffer, 0x00, MAX_BUFFER_SIZE + 1);
  int status = ::recv(m_socket, buffer, MAX_BUFFER_SIZE, 0);

  if (status == -1) {
    std::cout << "ERROR: recv error" << std::endl;
    return (0);
  }
  else if (status == 0)
    return (0);
  else {
    mes = buffer;
    return (status);
  }
}
