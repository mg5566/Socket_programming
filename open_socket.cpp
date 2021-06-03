#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(void) {
    int temp_fd;

    temp_fd = socket(PF_INET, SOCK_STREAM, 0);

    if (temp_fd < 0)
        std::cout << "Error: can't open socket" << std::endl;
    else
        std::cout << "Socket file descriptor : " << temp_fd << std::endl;

    close(temp_fd);

    return (0);
}