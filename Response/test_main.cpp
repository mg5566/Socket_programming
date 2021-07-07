#include "Response_Generator.hpp"

#include <iostream>
#include <string>
#include <map>
#include <vector>

int main(void) {
  std::string file_name = "text.txt";
  std::map<std::string, std::vector<std::string> > header_map;
  /* set header map */
  std::vector<std::string> vec;
  vec.push_back("127.0.0.1");
  // header_map["Host"] = {"127.0.0.1"};
  header_map["Host"] = vec; 
  vec.clear();
  vec.push_back("100");
  header_map["Content-Length"] = vec; 
  vec.clear();
  vec.push_back("de-DE");
  vec.push_back("en-CA");
  header_map["Content-Lengauge"] = vec;
  // header_map["Content-Lengauge"] = {"de-DE", "en-CA"};


  std::string res_msg;
  Response_Generator rg;

    // rg.set_res_msg(res_msg);
  rg.set_start_line(res_msg);
  rg.set_headers(res_msg, header_map);
  rg.set_entity_body(res_msg, file_name);
//   res_msg = rg.get_res_msg();
  std::cout << res_msg << std::endl;

    
  return (0);
}