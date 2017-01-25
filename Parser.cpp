#include <stdexcept>
#include "Parser.hpp"

namespace nts
{
  Parser::Parser() : m_index(0)
  {
  }

  Parser::Parser(Parser const &other) : m_str(other.m_str), m_index(0)
  {
  }

  Parser::~Parser()
  {
  }

  Parser &Parser::operator=(Parser const &other)
  {
    if (this != &other)
      {
	m_str = other.m_str;
	m_index = other.m_index;
      }
    return (*this);
  }

  void Parser::feed(std::string const &input)
  {
    m_str << input;
  }

  void Parser::parseTree(t_ast_node &root)
  {
  }

  //
  // Entry point of the parsing
  //

  t_ast_node *Parser::createTree()
  {
    t_ast_node *root = new t_ast_node();
    int         input_char;

    // Node creation
    root->type = DEFAULT;
    root->children = new std::vector<t_ast_node *>();
    root->lexeme = m_str.str();

    while (true)
      {
	input_char = m_str.get();
	switch (input_char)
	  {
	  // Comment
	  case '#':
	    root->children.push_back(this->createTreeComment(input_char));
	    break;
	  // Section
	  case '.':
	    root->children.push_back(this->createTreeSection(input_char));
	    break;
	  // Newline
	  case '\n':
	    root->children.push_back(this->createTreeNewline(input_char));
	    break;
	  // End of file
	  case EOF:
	    return (root);
	  // Space of tab
	  case ' ':
	  case '\t':
	    break;
	  // Other
	  default:
	    throw new std::exception(); // TODO: create specific exception
	    break;
	  }
      }
  }

  t_ast_node *Parser::createTreeComment(int input_char)
  {
    t_ast_node *comment = new t_ast_node();

    // Node creation
    comment->type = COMMENT;
    comment->children = nullptr;
    comment->lexeme += input_char;

    while (true)
      {
	intput_char = m_str.peek();
	if (input_char == '\n' || input_char == EOF)
	  {
	    return (comment);
	  }
	comment->lexeme += input_char;
	comment->value += input_char;
	m_str.get();
      }
  }

  t_ast_node *Parser::createTreeSection(int input_char)
  {
    int peek = m_str.peek();

    if (peek == 'c')
      {
	return (this->createTreeChipsetsSection(input_char));
      }
    else if (peek = 'l')
      {
	return (this->createTreeLinksSection(input_char));
      }
    else
      {
	throw new std::exception(); // TODO: create specific exception
      }
  }

  t_ast_node *Parser::createTreeNewline(int input_char)
  {
    t_ast_node *newline = new t_ast_node();

    // Node creation
    newline->type = NEWLINE;
    newline->children = nullptr;
    newline->lexeme += input_char;
    newline->value += input_char;

    return (newline);
  }

  t_ast_node *Parser::createTreeChipsetsSection(int input_char)
  {
    t_ast_node *section = new t_ast_node();

    // Node creation
    section->type = SECTION;
    section->children = new std::vector<t_ast_node *>();
    section->lexeme += input_char;

    char nameBuf[9];
    m_str.get(nameBuf, 8);
    std::string name(nameBuf);

    // Check if the section name is good
    if (name != "chipsets")
      {
	throw new std::exception(); // TODO: create specific exception
      }

    section->lexeme += name;
    section->value = name;
  }
}