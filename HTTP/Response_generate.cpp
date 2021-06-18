#include "Response_generate.hpp"

Response_Generate::Response_Generate() : response_message(NULL) {}

Response_Generate::~Response_Generate() {}

void Response_Generate::gerenate_response_message(void) {
  gen_start_line();
  gen_header();
  gen_entity();
}

void Response_Generate::gen_start_line() {}

void Response_Generate::gen_header() {}

void Response_Generate::gen_entity() {}
