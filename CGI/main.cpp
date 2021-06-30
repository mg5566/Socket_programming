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
  std::cout << temp[0] << std::endl;  // 출력은 되는데, 왜 temp[0] arr[0] 는 안찍히는가?!
  temp[1] = strdup("CONTENT_LENGTH=300");
  temp[2] = strdup("CONTENT_TYPE=aa");
  temp[3] = strdup("GATEWAY_INTERFACE=aaa");
  temp[4] = strdup("PATH_INFO=cgi_test");
  temp[5] = strdup("PATH_TRANSLATED=aaa");
  temp[6] = strdup("QUERY_STRING=aaa");
  temp[7] = strdup("REMOTE_ADDR=aaa");
  temp[8] = strdup("REMOTE_IDENT=aaa");
  temp[9] = strdup("REMOTE_USER=aaa");
  temp[10] = strdup("REQUEST_METHOD=GET");
  temp[11] = strdup("REQUEST_URI=aaa");
  temp[12] = strdup("SCRIPT_NAME=aaa");
  temp[13] = strdup("SERVER_PROTOCOL=HTTP/1.1");
  temp[14] = strdup("REDIRECT_STATUS=CGI");
  temp[15] = strdup("SCRIPT_FILENAME=test.html");
  temp[16] = NULL;

  return (temp);
}

void test_print_array(char **arr) {
  int idx = 0;
  while (arr[idx]) {
    std::cout << "arr[" << idx << "] = " << arr[idx] << std::endl;
    ++idx;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3)
    perror("invalid argument");
  else {
    std::cout << "valid argument" << std::endl;
    char **envp;
    pid_t pid;
    int pipe_fd[2];

    int ret;
    char buf[3000];

    envp = init_envp();
    std::cout << "test envp[0] : " << envp[0] << std::endl;
    test_print_array(envp);
    test_print_array(argv);

    pid = fork();
    //pipe(pipe_fd);
    //dup2(pipe_fd[1], 1);
    if (pid < 0)
      perror("fail fork process");
    else if (pid > 0) {
      std::cout << "in parent" << std::endl;
      waitpid(pid, NULL, 0);
      std::cout << "done wait" << std::endl;
      ret = read(pipe_fd[0], buf, 3000);
      buf[ret] = '\0';
      std::cout << buf << std::endl;
    }
    else if (pid == 0) {
      std::cout << "in child" << std::endl;
      //if (execve("/usr/local/bin/php-cgi", ++argv, envp) == -1)
      execve("/usr/local/bin/php-cgi", ++argv, envp);
      exit(0);
    }
    close(pipe_fd[0]);
    close(pipe_fd[1]);

  }
  return (0);
}
