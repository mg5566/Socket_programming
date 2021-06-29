#ifndef SOCKETMANAGER_HPP
#define SOCKETMANAGER_HPP

#include "webserv.hpp"
#include "Kqueue.hpp"
#include "Listening.hpp"
#include "Connection.hpp"

class Kqueue;
class Listening;
class Connection;

class SocketManager {
private:
	std::vector<Listening*>		listening;

	Connection	*connections;
	size_t		connection_n;
	Connection	*free_connections;
	size_t		free_connection_n;

public:
	SocketManager(std::multimap<in_port_t, in_addr_t> &addrs, Kqueue *kq);
	~SocketManager();

	void		init_socket_manager(std::multimap<in_port_t, in_addr_t> &addrs);

	int			open_listening_sockets(Kqueue *kq);
	void		close_listening_sockets();

	Connection*	get_connection(socket_t s);
	void		free_connection(Connection *c);
	void		close_connection(Connection *c);

	const std::vector<Listening*>	&get_listening() const;
	size_t		get_listening_size() const;
};

#endif