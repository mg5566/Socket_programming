#include "Request_parse.hpp"
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <string>
#include <iostream>

#define PORT 1234
#define BACK_LOG 10
#define QUEUE_SIZE 10
#define BUFFER_SIZE 1024

void print_error(std::string str) {
    perror(str.c_str());
    exit(1);
}

int main(void) {
    int server_sock;
    int client_sock;
    int sock_optval = 1;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
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
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(1234);  // port is 1234
    /* bind */
    ret = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    if (ret == -1)
        print_error("bind");

    /* listen */
    ret = listen(server_sock, 10);  // max back log is 10
    if (ret == -1)
        print_error("listen");

    int kq;
    struct kevent sock_event;
    struct kevent *kqueue_event;
    int event_cnt;

    /* create kernel queue */
    kq = kqueue();
    if (kq == -1)
        print_error("kqueue");
    /* set event */
    EV_SET(&sock_event, server_sock, EVFILT_READ, EV_ADD, 0, 0, NULL);
    ret = kevent(kq, &sock_event, 1, NULL, 0, NULL);
    if ( ret == -1 )
        print_error("kevent socket event");

    kqueue_event = (struct kevent *)malloc(sizeof(struct kevent) * QUEUE_SIZE);
    /* loop to process events */
    while (1) {
        /* wait for events to occur */
        event_cnt = kevent(kq, NULL, 0, kqueue_event, QUEUE_SIZE, NULL);
        if (event_cnt == -1) {
            close(server_sock);
            close(kq);
            print_error("kevent queue event");
        }

        /* check what find of event */
        for (int i = 0; i < event_cnt; ++i) {  // 전위 연산은 센스
            /* server socker event */
            int sock = kqueue_event[i].ident;
            if (sock == server_sock) {
                socklen_t socklen;
                client_sock= accept(server_sock, (struct sockaddr *)&client_addr, &socklen);
                /* add client socket to event */
                EV_SET(&sock_event, client_sock, EVFILT_READ, EV_ADD, 0, 0, NULL);
                ret = kevent(kq, &sock_event, 1, NULL, 0, NULL);
                if (ret == -1) {
                    close(server_sock);
                    close(client_sock);
                    close(kq);
                    print_error("kevent socket event");
                }
            /* client socket event : recive request message */
            } else {
                // 향후 logic 을 다듬어야합니다.
                char buf[BUFFER_SIZE];
                std::string str;
                // getline 을 사용해보고 싶지만 실패 ㅠㅠ
                int len = read(sock, buf, BUFFER_SIZE);
                buf[len] = '\0';
                str = buf;

                Request_Parse parser(str);
                parser.run_parsing();
                str.clear();
            }
        } 
    } 

    return (0);
}
/*
int main(void) {
    std::string buffer;

    buffer += "POST /cgi-bin/process.cgi HTTP/1.1\r\n";
    buffer += "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n";
    buffer += "Host: www.tutorialspoint.com\r\n";
    buffer += "Content-Type: text/xml; charset=utf-8\r\n";
    buffer += "Content-Length: length\r\n";
    buffer += "Accept-Language: en-us\r\n";
    buffer += "Accept-Encoding: gzip, deflate\r\n";
    buffer += "Connection: Keep-Alive\r\n";
    buffer += "\r\n";
    buffer += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    buffer += "<string xmlns=\"http://clearforest.com/\">string</string>";

    std::cout << "test print buffer" << std::endl;
    std::cout << buffer << std::endl;

    Request_Parse parser(buffer);

    return (0);
}
*/