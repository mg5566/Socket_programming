#include <iostream>
#include <unistd.h>
#include <sys/socket.h>  // socket
#include <sys/types.h>
#include <netinet/in.h>  // sockaddr_in
#include <fcntl.h>  // fcntl

#define PORT 1234
#define NEW_PORT 3333
#define BACK_LOG 10

int main(void) {
    int socket_fd;

    // create socket
    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    std::cout << "socket creation success" << std::endl;

    // for test socket file descriptor
    if (socket_fd < 0) {
        std::cout << "Error: can't open socket" << std::endl;
        close(socket_fd);
    }
    else
        std::cout << "Socket file descriptor : " << socket_fd << std::endl;

    // socket for reusing
    int on = 1;
    if ( setsockopt (socket_fd, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
        return (-1);

    // bind socket using port
    sockaddr_in addr;
    // set address of socket
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;  // accept any address
    addr.sin_port = htons(PORT);
    if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0) {
        std::cout << "fail to bind PORT(1234)" << std::endl;
        close(socket_fd);
        return (-1);
    }
    /* 안됩니다.... 어찌 해야하오...
    // test multy port
    // add new port
    sockaddr_in addr_new;
    // set address of socket
    addr_new.sin_family = AF_INET;
    addr_new.sin_addr.s_addr = INADDR_ANY;  // accept any address
    addr_new.sin_port = htons(NEW_PORT);
    if (bind(socket_fd, (struct sockaddr *)&addr_new, sizeof(struct sockaddr)) < 0) {
        std::cout << "fail to add new_port" << std::endl;
        close(socket_fd);
        return (-1);
    }
    */
    std::cout << "finish bind" << std::endl;
    // backlog 크기만큼 연결을 받을 수 있습니다.
    if (listen(socket_fd, BACK_LOG) < 0) {
        close(socket_fd);
        return (-1);
    }
    std::cout << "finish listen 10 connection available" << std::endl;

    // set fd_set
    fd_set readfds, allfds;

    FD_ZERO(&readfds);
    FD_SET(socket_fd, &readfds);

    int max_fd;
    struct timeval tv;

    max_fd = socket_fd;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    //fcntl(socket_fd, F_SETFL, O_NONBLOCK);
    while (1) {
        allfds = readfds;
        /*
        std::cout << "max fd is " << max_fd << std::endl;
        // block
        int select_result = select(max_fd + 1, &allfds, NULL, NULL, NULL);
        // non-blocking
        //int select_result = select(max_fd + 1, &allfds, NULL, NULL, &tv);
        std::cout << "select result is " << select_result << std::endl;

        if (FD_ISSET(socket_fd, &allfds)) {
            std::cout << "socket_fd is caught" << std::endl;
            int addr_len = 0;
            int new_client = accept(socket_fd, (sockaddr *)&addr, (socklen_t *)&addr_len);
            std::cout << "success accept, create new_client " << new_client << std::endl;
            FD_SET(new_client, &readfds);

            if (new_client > max_fd) {
                max_fd = new_client;
                std::cout << "update max_fd" << std::endl;
            }
        }
        */
        int addr_len = 0;
        int new_client = accept(socket_fd, (sockaddr *)&addr, (socklen_t *)&addr_len);
        std::cout << "success accept, create new_client " << new_client << std::endl;
        std::cout << "max_fd " << max_fd << std::endl;
        if (new_client > max_fd) {
            max_fd = new_client;
            std::cout << "update max_fd" << std::endl;
        }
        std::cout << "max_fd " << max_fd << std::endl;
        FD_SET(new_client, &readfds);
        allfds = readfds;
        int select_result = select(max_fd + 1, &allfds, NULL, NULL, NULL);
        std::cout << "select result : " << select_result << std::endl;
        for (int i = 3; i < max_fd + 1; ++i) {
            /*
            std::cout << "i = " << i << std::endl;
            char buffer[100];
            memset(buffer, 0x00, 100);
            int res;
            while ((res = read(i, &buffer, 100)) > 0) {
                std::cout << "res : " << res << std::endl;
                if (res > 0) buffer[res] = '\0';
                std::cout << "recv : " << buffer << std::endl;
            }
            */
            // request message
            if (FD_ISSET(i, &allfds)) {
                std::cout << "i = " << i << std::endl;
                // recv
                char buffer[10000];
                memset(buffer, 0x00, 10000);
                int res = read(i, &buffer, 10000);
                std::cout << "res : " << res << std::endl;
                if (res > 0) buffer[res] = '\0';
                std::cout << "recv : " << std::endl << buffer << std::endl;
            }
        }
        // close connection
        //close(new_client);
    }
    
    return (0);
}