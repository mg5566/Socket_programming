#include "Response_Generator.hpp"

#include <iostream>
#include <string>

int main(void) {
  std::string res_msg;
  Response_Generator rg;

    // rg.set_res_msg(res_msg);
  rg.set_start_line(res_msg);
  rg.set_header(res_msg);
//   res_msg = rg.get_res_msg();
  std::cout << res_msg << std::endl;

  return (0);
}