#ifndef CYCLE_HPP
#define CYCLE_HPP

#include "webserv.hpp"
#include "SocketManager.hpp"
#include "Kqueue.hpp"
#include "Request_parse.hpp"

class Cycle {
private:
	SocketManager	*sm;
	Kqueue			*kq;
	Request_Parse	*parser;

public:
	Cycle(std::multimap<in_port_t, in_addr_t> &addrs);
	~Cycle();
	
	void	webserv_cycle();
};

#endif