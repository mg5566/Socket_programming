#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <iostream>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <map>
#include <vector>

typedef	int					socket_t;
typedef intptr_t			int_t;
typedef uintptr_t			uint_t;
typedef u_short				in_port_t;

#define DEFAULT_CONNECTIONS	512
#define LISTEN_BACKLOG		511
#define BUF_SIZE			30000
#define nonblocking(s)		fcntl(s, F_SETFL, O_NONBLOCK)
#define close_socket		close

#define WEBSERV_CONTINUE	1
#define WEBSERV_OK			0
#define WEBSERV_ERROR		-1

#endif