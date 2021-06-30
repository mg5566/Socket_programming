class CGI {
  private:
    char **envp;
    char **argv;

  public:
    CGI();
    ~CGI();

    // 환경변수 관련 함수
    set_env();
    get_env();

    // path 관련 함수
    set_argv();
    get_argv();

    // execve 관련 함수
    excute_CGI();

    // test print 함수
    test_print();


};
