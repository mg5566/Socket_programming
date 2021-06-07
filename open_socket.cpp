#include <iostream>
#include <unistd.h>
#include <sys/socket.h>  // socket
#include <sys/types.h>
#include <netinet/in.h>  // sockaddr_in

#define PORT 1234
#define BACK_LOG 10

int main(void) {
    int socket_fd;

    // create socket
    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    std::cout << "socket creation success" << std::endl;
    /*
    ** for test socket file descriptor
    if (socket_fd < 0) {
        std::cout << "Error: can't open socket" << std::endl;
        close(socket_fd);
    }
    else
        std::cout << "Socket file descriptor : " << socket_fd << std::endl;
    */

    // bind socket using port
    sockaddr_in addr;
    // set address of socket
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;  // accept any address
    addr.sin_port = htons(PORT);
    if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0) {
        close(socket_fd);
        return (-1);
    }
    std::cout << "finish bind" << std::endl;
    // backlog 크기만큼 연결을 받을 수 있습니다.
    if (listen(socket_fd, BACK_LOG) < 0) {
        close(socket_fd);
        return (-1);
    }
    std::cout << "finish listen 10 connection available" << std::endl;
    
    /* accept */
    int client_fd;
    int addr_len;

    client_fd = accept(socket_fd, (sockaddr *)&addr, (socklen_t *)&addr_len);
    if (client_fd == -1) {
        close(socket_fd);
        close(client_fd);
        return (-1);

    }




    

    return (0);
}