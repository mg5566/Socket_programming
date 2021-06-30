/*
** fork 를 통해서 자식프로세스를 만들고, pipe 를 통해서 프로세스간 통신을 하는 test file 입니다.
*/
#include <unistd.h>
#include <stdlib.h>

#include <iostream>

#define BUFFER_SIZE 100

int main(void) {
  pid_t pid;
  int pipe_fd[2];
  int bytes = 1;
  char buf[BUFFER_SIZE];

  pipe(pipe_fd);
  pid = fork();

  if (pid > 0) {  // parent
    close(pipe_fd[1]);
    bytes = read(pipe_fd[0], buf, BUFFER_SIZE);
    buf[bytes] = '\0';
    std::cout << buf << std::endl;
  } else if (pid == 0) {  // child
    close(pipe_fd[0]);
    dup2(pipe_fd[1], 1);
    std::cout << "fucking webserv" << std::endl;
    std::cout << "another fucking" << std::endl;
    std::cout << "other fucking" << std::endl;
    exit(1);
  }
  close(pipe_fd[0]);
  close(pipe_fd[1]);

  return (0);
}
