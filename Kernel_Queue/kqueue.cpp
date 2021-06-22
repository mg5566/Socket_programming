#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

void print_error(std::string str) {
    perror(str.c_str());
    exit(1);
}

int main(void) {
    int server_sock;
    int sock_optval = 1;
    struct sockaddr_in sin;
    int ret;

    /* open server socket */
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    /* set socket option to be reusable */
    if ( setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &sock_optval, sizeof(sock_optval)) == -1 )
        print_error("set socket option");
        /*
        perror("setsockopt");
        exit(1);
        */
    

    /* set struct sockaddr */
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(1234);  // port is 1234
    /* bind */
    ret = bind(server_sock, (struct sockaddr *)&sin, sizeof(struct sockaddr));
    if (ret == -1)
        print_error("bind");

    /* listen */
    ret = listen(server_sock, 10);  // max back log is 10
    if (ret == -1)
        print_error("listen");

    int kq;
    struct kevent k_ev;

    /* create kernel queue */
    kq = kqueue();
    if (kq == -1)
        print_error("kqueue");
    /* set event */
    EV_SET(&k_ev, server_sock, EVFILT_READ, EV_ADD, 0, 0, NULL);
    ret = kevent(kq, &k_ev, 1, NULL, 0, NULL);
    if ( ret == -1 )
        print_error("kevent");
    


    return (0);
}