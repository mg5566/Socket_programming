#ifndef LISTENING_HPP
#define LISTENING_HPP

#include "webserv.hpp"
#include "SocketManager.hpp"
#include "Connection.hpp"

class SocketManager;
class Connection;

class Listening {
private:
	socket_t			fd;
	
	struct sockaddr_in	sockaddr;
	socklen_t			socklen;

	int					type;
	int					backlog;

	Connection			*connection;

public:
	Listening(in_port_t _port, in_addr_t _ipaddr);
	~Listening();

	int_t		open_listening_socket(SocketManager *sm);

	void		set_listening_connection(Connection *c);

	Connection	*get_listening_connection() const;
	socket_t	get_fd() const;
};

#endif