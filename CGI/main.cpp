#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#include <string>
#include <iostream>

/*
void init_envp(char ***envp) {
    std::cout << "before allocate memory" << std::endl;
    *envp = (char **)malloc(sizeof(char *) * 14);
    std::cout << "after malloc" << std::endl;
    *envp[0] = strdup("AUTH_TYPE=aaa");
    std::cout << "0" << std::endl;
    *envp[1] = strdup("CONTENT_LENGTH=0");
    std::cout << "1" << std::endl;
    std::cout << *envp[0] << std::endl << *envp[1] << std::endl;
    *envp[2] = strdup("CONTENT_TYPE=aa");
    std::cout << "2" << std::endl;
    *envp[3] = strdup("GATEWAY_INTERFACE=aaa");
    std::cout << "3" << std::endl;
    *envp[4] = strdup("PATH_INFO=aaa");
    std::cout << "4" << std::endl;
    *envp[5] = strdup("PATH_TRANSLATED=aaa");
    std::cout << "5" << std::endl;
    *envp[6] = strdup("QUERY_STRING=aaa");
    std::cout << "6" << std::endl;
    *envp[7] = strdup("REMOTE_ADDR=aaa");
    std::cout << "7" << std::endl;
    *envp[8] = strdup("REMOTE_IDENT=aaa");
    std::cout << "8" << std::endl;
    *envp[9] = strdup("REMOTE_USER=aaa");
    std::cout << "9" << std::endl;
    *envp[10] = strdup("REQUEST_METHOD=GET");
    std::cout << "10" << std::endl;
    *envp[11] = strdup("REQUEST_URI=aaa");
    std::cout << "11" << std::endl;
    *envp[12] = strdup("SCRIPT_NAME=aaa");
    std::cout << "12" << std::endl;
    *envp[13] = strdup("SERVER_PROTOCOL=HTTP/1.1");
    std::cout << "13" << std::endl;
    *envp[14] = NULL;
    std::cout << "14" << std::endl;
}
*/

int main(int argc, char *argv[]) {
  if (argc != 2)
    perror("invalid argument");
  else {
    char *envp[] = {
      "AUTH_TYPE=aaa",
      "CONTENT_LENGTH=0",
      "CONTENT_TYPE=aa",
      "GATEWAY_INTERFACE=aaa",
      "PATH_INFO=aaa",
      "PATH_TRANSLATED=aaa",
      "QUERY_STRING=aaa",
      "REMOTE_ADDR=aaa",
      "REMOTE_IDENT=aaa",
      "REMOTE_USER=aaa",
      "REQUEST_METHOD=GET",
      "REQUEST_URI=aaa",
      "SCRIPT_NAME=aaa",
      "SERVER_PROTOCOL=HTTP/1.1",
      NULL
    };
    pid_t pid;
    int pipe_fd[2];

    pid = fork();
    if (pid < 0)
      perror("fail fork process");
    else if (pid > 0)
      waitpid(pid, NULL, 0);
    else if (pid == 0) {
      pipe(pipe_fd);
      dup2(pipe_fd[0], 0);
      dup2(pipe_fd[1], 1);
      execve("./cgi_tester", ++argv, envp);
      exit(0);
    }

  }
  return (0);
}