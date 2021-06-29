#include "Kqueue.hpp"

Kqueue::Kqueue()
: kq(-1), nchanges(0), nevents(0), change_list(NULL), event_list(NULL)
{
	kqueue_init();
}

Kqueue::~Kqueue()
{
	kqueue_done();
}

int_t	Kqueue::kqueue_init()
{
	kcf.changes = 512;
	kcf.events = 512;
	ts.tv_sec = 5;
	ts.tv_nsec = 0;

	if (kq == -1) {
		kq = kqueue();
		if (kq == -1) {
			std::cerr << "kqueue() failed..." << std::endl;
			return WEBSERV_ERROR;
		}
	}

	change_list = new struct kevent[kcf.changes]();
	if (change_list == NULL) {
		return WEBSERV_ERROR;
	}
	event_list = new struct kevent[kcf.events]();
	if (event_list == NULL) {
		return WEBSERV_ERROR;
	}
	max_changes = kcf.changes;
	nevents = kcf.events;
	return WEBSERV_OK;
}

void	Kqueue::kqueue_done() {
	if (close(kq) == -1) {
		std::cerr << "kqueue close() failed..." << std::endl;
	}
	kq = -1;
	delete[] change_list;
	delete[] event_list;
	max_changes = 0;
	nchanges = 0;
	nevents = 0;
}

// Connection 하나 등록
int		Kqueue::kqueue_add_event(Connection *c)
{
	EV_SET(&change_list[nchanges], c->get_fd(), EVFILT_READ, EV_ADD, 0, 0, c);	// udata = Connection
	++nchanges;
	if (kevent(kq, change_list, nchanges, NULL, 0, NULL) == -1) {
		std::cerr << "kevent() failed..." << std::endl;
		return WEBSERV_ERROR;
	}
	nchanges = 0;
	return WEBSERV_OK;
}

int		Kqueue::kqueue_del_event(Connection *c)
{
	EV_SET(&change_list[nchanges], c->get_fd(), EVFILT_READ, EV_DELETE, 0, 0, c);	// udata = Connection
	++nchanges;
	if (kevent(kq, change_list, nchanges, NULL, 0, NULL) == -1) {
		std::cerr << "kevent() failed..." << std::endl;
		return WEBSERV_ERROR;
	}
	nchanges = 0;
	return WEBSERV_OK;
}

// int_t	Kqueue::kqueue_process_events(SocketManager *sm)
int_t	Kqueue::kqueue_process_events(SocketManager *sm, Request_Parse *parser)
{
	int		events;

	events = kevent(kq, NULL, 0, event_list, (int)nevents, &ts);
	if (events == -1) {
		std::cerr << "kevent() failed..." << std::endl;
		return WEBSERV_ERROR;
	}

	for (int_t i = 0; i < events; ++i) {
		Connection *c = (Connection*)event_list[i].udata;

		if (event_list[i].flags & EV_ERROR) {
			std::cerr << "kevent() error on " << (int)event_list[i].ident << std::endl;
			continue ;
		}
		if (event_list[i].flags & EV_EOF) {
			std::cout << "Client disconnected..." << std::endl;
			kqueue_del_event(c);
			sm->close_connection(c);
		}
		else if (c->get_listen()) {
			Connection *conn = c->event_accept(sm);
			kqueue_add_event(conn);
		}
		else
		{
			// std::cout << "data: " << event_list[i].data << std::endl;
			recv(c->get_fd(), c->buffer, event_list[i].data, 0);
			// parsing후 처리하는 부분
			std::cout << c->buffer << std::endl;
			(*parser).set_message(c->buffer);
			(*parser).run_parsing();
			print_parsed_data((*parser).get_start_line_map(), (*parser).get_header_map(), (*parser).get_entity_str());

			
			// response 만들어서 send하는 부분
			send(c->get_fd(), c->buffer, strlen(c->buffer), 0);
			memset(c->buffer, 0, event_list[i].data);
		}
	}
	return WEBSERV_OK;
}