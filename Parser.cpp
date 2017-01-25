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

    // Get the name (must be "chipsets")
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

    // Check that it is followed by a ':'
    input_char = m_str.get();
    if (input_char != ':')
      {
	throw new std::exception(); // TODO: create specific exception
      }
    section->lexeme += input_char;

    while (true)
      {
	input_char = m_str.peek();
	switch (input_char)
	  {
	  // End of file or new Section
	  case 'EOF':
	  case '.':
	    return (section);
	  // Newline
	  case '\n':
	    section->child.push_back(this->createTreeNewline(m_str.get()));
	    break;
	  // Space
	  case ' ':
	  case '\t':
	    break;
	  // Chipset
	  default:
	    section->child.push_back(this->createTreeChipset());
	  }
      }
  }

  t_ast_node *Parser::createTreeLinksSection(int input_char)
  {
    t_ast_node *section = new t_ast_node();

    // Node creation
    section->type = SECTION;
    section->children = new std::vector<t_ast_node *>();
    section->lexeme += input_char;

    // Get the name (must be "links")
    char nameBuf[6];
    m_str.get(nameBuf, 5);
    std::string name(nameBuf);

    // Check if the section name is good
    if (name != "links")
      {
	throw new std::exception(); // TODO: create specific exception
      }

    section->lexeme += name;
    section->value = name;

    // Check that it is followed by a ':'
    input_char = m_str.get();
    if (input_char != ':')
      {
	throw new std::exception(); // TODO: create specific exception
      }
    section->lexeme += input_char;

    while (true)
      {
	input_char = m_str.peek();
	switch (input_char)
	  {
	  // End of file or new Section
	  case 'EOF':
	  case '.':
	    return (section);
	  // Newline
	  case '\n':
	    section->child.push_back(this->createTreeNewline(m_str.get()));
	    break;
	  // Space
	  case ' ':
	  case '\t':
	    break;
	  // Chipset
	  default:
	    section->child.push_back(this->createTreeLink());
	  }
      }
  }

  t_ast_node *Parser::createTreeChipset()
  {
    int peek = m_str.peek();

    switch (peek)
      {
      case 'i':
      case 'c':
	return (this->createTreeInputChipset());
      case 't':
      case 'f':
      case 'o':
	return (this->createTreeNormalChipset());
      default:
	throw new std::exception(); // TODO: create specific exception
      }
  }

  t_ast_node *Parser::createTreeLink()
  {
    t_ast_node *link = new t_ast_node();
    int         input_char;
    int         nbLinkEnd = 0;

    // Node creation
    link->type = LINK;
    link->children = new std::vector<t_ast_node *>();

    while (true)
      {
	input_char = m_str.peek();
	switch (input_char)
	  {
	  case ' ':
	  case '\t':
	    break;
	  case '\n':
	    link->children.push_back(this->createTreeNewline(m_str.get()));
	  case 'EOF':
	    throw new std::exception(); // TODO: create specific exception
	  default:
	    nbLinkEnd++;
	    link->children.push_back(this->createTreeLinkEnd());
	    if (nbLinkEnd == 2)
	      {
		return (link);
	      }
	  }
      }
  }

  t_ast_node *Parser::createTreeLinkEnd()
  {
    t_ast_node *end = new t_ast_node();
    int         input_char;
    int         nbLinkEnd = 0;

    // Node creation
    end->type = LINK;
    end->children = new std::vector<t_ast_node *>();

    // Get name
    while (true)
      {
	input_char = m_str.get();

	if (input_char == EOF)
	  {
	    throw new std::exception(); // TODO: create specific exception
	  }

	if (input_char == ':')
	  {
	    break;
	  }
	if (std::isalnum(input_char))
	  {
	    end->lexeme += input_char;
	    end->value += input_char;
	  }
	else
	  {
	    throw new std::exception(); // TODO: create specific exception
	  }
      }

    while (true)
      {
	input_char = m_str.peek();
	switch (input_char)
	  {
	  case '\n':
	    end->children.push_back(this->createTreeNewline(m_str.get()));
	    break;
	  case ' ':
	  case '\t':
	    break;
	  case EOF:
	    throw new std::exception(); // TODO: create specific exception
	  default:
	    end->children.push_back(this->createTreeString());
	    return (end);
	  }
      }
  }
  
}