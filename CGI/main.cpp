#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#include <string>
#include <iostream>

//void init_envp(char ***envp) {
char **init_envp() {
  char **temp;

    std::cout << "before allocate memory" << std::endl;
    temp = (char **)malloc(sizeof(char *) * 16);
    std::cout << "after malloc" << std::endl;
    temp[0] = strdup("AUTH_TYPE=aaa");
    // *envp[0] = temp;
    temp[1] = strdup("CONTENT_LENGTH=0");
    // *envp[1] = temp;
    temp[2] = strdup("CONTENT_TYPE=aa");
    // *envp[2] = temp;
    temp[3] = strdup("GATEWAY_INTERFACE=aaa");
    // *envp[3] = temp;
    temp[4] = strdup("PATH_INFO=cgi_test");
    // *envp[4] = temp;
    temp[5] = strdup("PATH_TRANSLATED=aaa");
    // *envp[5] = temp;
    temp[6] = strdup("QUERY_STRING=aaa");
    // *envp[6] = temp;
    temp[7] = strdup("REMOTE_ADDR=aaa");
    // *envp[7] = temp;
    temp[8] = strdup("REMOTE_IDENT=aaa");
    // *envp[8] = temp;
    temp[9] = strdup("REMOTE_USER=aaa");
    // *envp[9] = temp;
    temp[10] = strdup("REQUEST_METHOD=GET");
    // *envp[10] = temp;
    temp[11] = strdup("REQUEST_URI=aaa");
    // *envp[11] = temp;
    temp[12] = strdup("SCRIPT_NAME=aaa");
    // *envp[12] = temp;
    temp[13] = strdup("SERVER_PROTOCOL=HTTP/1.1");
    temp[14] = strdup("REDIRECT_STATUS=CGI");
    temp[15] = strdup("SCRIPT_FILENAME=php-cgi");
    temp[16] = NULL;
    // *envp[13] = temp;
    // *envp[14] = NULL;

    return (temp);
}

int main(int argc, char *argv[]) {
  if (argc != 3)
    perror("invalid argument");
  else {
    /*
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
    */
    char **envp;
    pid_t pid;
    int pipe_fd[2];

    envp = init_envp();

    pid = fork();
    pipe(pipe_fd);
    //dup2(pipe_fd[0], 0);
    dup2(pipe_fd[1], STDOUT_FILENO);
    if (pid < 0)
      perror("fail fork process");
    else if (pid > 0)
      waitpid(pid, NULL, 0);
    else if (pid == 0) {
      //execve("./cgi_tester", ++argv, envp);
      execve("/usr/local/bin/php-cgi", ++argv, envp);
      exit(0);
    }
    close(pipe_fd[0]);
    close(pipe_fd[1]);

  }
  return (0);
}
