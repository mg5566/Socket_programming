#include <iostream>

int print_error(std::string str) {
    std::cout << str << std::endl;
    return (-1);
}

int main(int argc, char *argv[], char *envp[]) {
    if (argc != 2)
        return (print_error("Error : use ./webserv conf_file"));
    try {
        std::cout << "conf file : " << argv[1] << std::endl;
        int i = 0;
        while (envp[i]) {
            std::cout << envp[i] << std::endl;
            i++;
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return (0);
}