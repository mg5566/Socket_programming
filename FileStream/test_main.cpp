#include <fstream>
#include <iostream>

int main(void) {
  std::string file_name = "test.txt";

  // std::fstream open_file(file_name.data(), std::fstream::in | std::fstream::out | std::fstream::app);
  std::fstream read_file(file_name.data(), std::fstream::in);

  if (!read_file.is_open())
    exit(1);
  
  // read example
  std::string line;
  int idx = 0;

  while (getline(read_file, line)) {
    std::cout << idx++ << " : " << line << "|" << std::endl;
  }

  read_file.close();

  // write example, 아마도 CGI, POST 에서 사용할 것으로 예상됩니다.
  std::fstream write_file(file_name.data(), std::fstream::app);
  std::string str("written by Hakc3rs");

  write_file << str << std::endl;

  write_file.close();

  return (0);
}