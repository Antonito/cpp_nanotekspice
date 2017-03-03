#ifndef PARSER_HPP_
#define PARSER_HPP_

#include <string>
#include <sstream>
#include <map>
#include <memory>
#include "cpp_nanoTekSpice_parser.hpp"
#include "ComponentFactory.hpp"
#include "Input.hpp"
#include "Output.hpp"

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
    void deleteTree(t_ast_node *root) const;

  private:
    void parseSection(t_ast_node &section);
    void parseChipsets(t_ast_node &section);
    void parseLinks(t_ast_node &section);
    void parseComponent(t_ast_node &component);
    void parseLink(t_ast_node &link);
    void parseLinkEnd(t_ast_node &end);

    t_ast_node *createTreeSection(char input_char);
    t_ast_node *createTreeNewline(char input_char);
    t_ast_node *createTreeChipsetsSection(char input_char);
    t_ast_node *createTreeLinksSection(char input_char);
    t_ast_node *createTreeLink();
    t_ast_node *createTreeLinkEnd();
    t_ast_node *createTreeString();
    t_ast_node *createTreeChipset();
    void        clearInput();

    std::stringstream        m_str;
    std::vector<std::string> m_input;
    std::vector<std::string> m_component;
    std::map<std::string, bool> m_output;
  };
}

#endif // !PARSER_HPP_