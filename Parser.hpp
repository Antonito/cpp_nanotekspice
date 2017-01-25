#ifndef PARSER_HPP_
#define PARSER_HPP_

#include "cpp_nanoTekSpice_parser.hpp"

namespace nts
{
  class Parser : public IParser
  {
  public:
    Parser();
    Parser(Parser const &other);
    virtual ~Parser();

    Parser &operator=(Parser const &other);

    virtual void feed(std::string const &input);
    virtual void parseTree(t_ast_node &root);
    virtual t_ast_node *createTree();

  private:
    t_ast_node *createTreeComment(int input_char);
    t_ast_node *createTreeSection(int input_char);
    t_ast_node *createTreeNewline(int input_char);
    t_ast_node *createTreeChipsetsSection(int input_char);
    t_ast_node *createTreeLinksSection(int input_char);
    std::stringstream m_str;
  };
}

#endif // !PARSER_HPP_