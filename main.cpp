#include <fstream>
#include <sstream>
#include <iostream>
#include "cpp_nanoTekSpice_parser.hpp"
#include "Parser.hpp"

int main()
{
  std::ifstream     file("config.ini");
  std::stringstream ss;
  nts::Parser       parser;

  ss << file.rdbuf();
  parser.feed(ss.str());

  nts::t_ast_node *root = parser.createTree();

  return 0;
}