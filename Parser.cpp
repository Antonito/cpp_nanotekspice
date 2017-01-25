#include <stdexcept>
#include "Parser.hpp"

namespace nts
{
  Parser::Parser()
  {
  }

  Parser::Parser(Parser const &other)
  {
    m_str.str("");
    m_str << other.m_str.str();
  }

  Parser::~Parser()
  {
  }

  Parser &Parser::operator=(Parser const &other)
  {
    if (this != &other)
      {
	m_str.str("");
	m_str << other.m_str.str();
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
    t_ast_node *root = new t_ast_node(nullptr);
    int         inputChar;

    // Node creation
    root->type = ASTNodeType::DEFAULT;
    root->children = new std::vector<t_ast_node *>();
    root->lexeme = m_str.str();

    while (true)
      {
	inputChar = m_str.get();
	switch (inputChar)
	  {
	  // Section
	  case '.':
	    root->children->push_back(this->createTreeSection(inputChar));
	    break;
	  // Newline
	  case '\n':
	    root->children->push_back(this->createTreeNewline(inputChar));
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

  t_ast_node *Parser::createTreeSection(int inputChar)
  {
    int peek = m_str.peek();

    if (peek == 'c')
      {
	return (this->createTreeChipsetsSection(inputChar));
      }
    else if (peek == 'l')
      {
	return (this->createTreeLinksSection(inputChar));
      }
    else
      {
	throw new std::exception(); // TODO: create specific exception
      }
  }

  t_ast_node *Parser::createTreeNewline(int inputChar)
  {
    t_ast_node *newline = new t_ast_node(nullptr);

    // Node creation
    newline->type = ASTNodeType::NEWLINE;
    newline->children = nullptr;
    newline->lexeme += inputChar;
    newline->value += inputChar;

    return (newline);
  }

  t_ast_node *Parser::createTreeChipsetsSection(int inputChar)
  {
    t_ast_node *section = new t_ast_node(nullptr);

    // Node creation
    section->type = ASTNodeType::SECTION;
    section->children = new std::vector<t_ast_node *>();
    section->lexeme += inputChar;

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
    inputChar = m_str.get();
    if (inputChar != ':')
      {
	throw new std::exception(); // TODO: create specific exception
      }
    section->lexeme += inputChar;

    while (true)
      {
	inputChar = m_str.peek();
	switch (inputChar)
	  {
	  // End of file or new Section
	  case EOF:
	  case '.':
	    return (section);
	  // Newline
	  case '\n':
	    section->children->push_back(this->createTreeNewline(m_str.get()));
	    break;
	  // Space
	  case ' ':
	  case '\t':
	    break;
	  // Chipset
	  default:
	    section->children->push_back(this->createTreeChipset());
	  }
      }
  }

  t_ast_node *Parser::createTreeLinksSection(int inputChar)
  {
    t_ast_node *section = new t_ast_node(nullptr);

    // Node creation
    section->type = ASTNodeType::SECTION;
    section->children = new std::vector<t_ast_node *>();
    section->lexeme += inputChar;

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
    inputChar = m_str.get();
    if (inputChar != ':')
      {
	throw new std::exception(); // TODO: create specific exception
      }
    section->lexeme += inputChar;

    while (true)
      {
	inputChar = m_str.peek();
	switch (inputChar)
	  {
	  // End of file or new Section
	  case EOF:
	  case '.':
	    return (section);
	  // Newline
	  case '\n':
	    section->children->push_back(this->createTreeNewline(m_str.get()));
	    break;
	  // Space
	  case ' ':
	  case '\t':
	    break;
	  // Chipset
	  default:
	    section->children->push_back(this->createTreeLink());
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
    t_ast_node *link = new t_ast_node(nullptr);
    int         inputChar;
    int         nbLinkEnd = 0;

    // Node creation
    link->type = ASTNodeType::LINK;
    link->children = new std::vector<t_ast_node *>();

    while (true)
      {
	inputChar = m_str.peek();
	switch (inputChar)
	  {
	  case ' ':
	  case '\t':
	    break;
	  case '\n':
	    link->children->push_back(this->createTreeNewline(m_str.get()));
	  case EOF:
	    throw new std::exception(); // TODO: create specific exception
	  default:
	    nbLinkEnd++;
	    link->children->push_back(this->createTreeLinkEnd());
	    if (nbLinkEnd == 2)
	      {
		return (link);
	      }
	  }
      }
  }

  t_ast_node *Parser::createTreeLinkEnd()
  {
    t_ast_node *end = new t_ast_node(nullptr);
    int         inputChar;
    int         nbLinkEnd = 0;

    // Node creation
    end->type = ASTNodeType::LINK_END;
    end->children = new std::vector<t_ast_node *>();

    // Get name
    while (true)
      {
	inputChar = m_str.get();

	if (inputChar == EOF)
	  {
	    throw new std::exception(); // TODO: create specific exception
	  }

	if (inputChar == ':')
	  {
	    break;
	  }
	if (std::isalnum(inputChar))
	  {
	    end->lexeme += inputChar;
	    end->value += inputChar;
	  }
	else
	  {
	    throw new std::exception(); // TODO: create specific exception
	  }
      }

    while (true)
      {
	inputChar = m_str.peek();
	switch (inputChar)
	  {
	  case '\n':
	    end->children->push_back(this->createTreeNewline(m_str.get()));
	    break;
	  case ' ':
	  case '\t':
	    break;
	  case EOF:
	    throw new std::exception(); // TODO: create specific exception
	  default:
	    end->children->push_back(this->createTreeString());
	    return (end);
	  }
      }
  }

  t_ast_node *Parser::createTreeString()
  {
    t_ast_node *str = new t_ast_node(nullptr);
    int         inputChar;

    // Node creation
    str->type = ASTNodeType::STRING;
    str->children = nullptr;

    while (true)
      {
	inputChar = m_str.peek();
	if (std::isalnum(inputChar))
	  {
	    str->lexeme += inputChar;
	    str->value += inputChar;
	    m_str.get();
	  }
	else
	  {
	    return (str);
	  }
      }
  }

  t_ast_node *Parser::createTreeInputChipset()
  {
    t_ast_node *chipset = new t_ast_node(nullptr);
    int         inputChar;

    // Node creation
    chipset->type = ASTNodeType::COMPONENT;
    chipset->children = new std::vector<t_ast_node *>();

    std::string name;
    inputChar = m_str.peek();

    // name should be "input" or "clock" (5 char each)
    char nameBuf[6];

    m_str.get(nameBuf, 5);
    name = std::string(nameBuf);

    if (name != "input" && name != "clock")
      {
	throw new std::exception(); // TODO: create specific exception
      }

    chipset->lexeme += name;
    chipset->value += name;

    inputChar = m_str.peek();
    if (inputChar != ' ' && inputChar != '\t')
      {
	throw new std::exception(); // TODO: create specific exception
      }

    bool gettingName = true;
    while (gettingName)
      {
	inputChar = m_str.peek();
	switch (inputChar)
	  {
	  case ' ':
	  case '\t':
	    break;
	  case '\n':
	    throw new std::exception(); // TODO: create specific exception
	  default:
	    chipset->children->push_back(this->createTreeString());
	    gettingName = false;
	    break;
	  }
      }

    while (true)
      {
	inputChar = m_str.peek();
	switch (inputChar)
	  {
	  case ' ':
	  case '\t':
	    break;
	  case '\n':
	  case '(':
	    m_str.get();
	    chipset->children->push_back(this->createTreeString());
	    inputChar = m_str.get();
	    if (inputChar != ')')
	      {
		throw new std::exception(); // TODO: create specific exception
	      }
	    return (chipset);
	  }
      }
  }

  t_ast_node *Parser::createTreeNormalChipset()
  {
    t_ast_node *chipset = new t_ast_node(nullptr);
    int         inputChar;

    // Node creation
    chipset->type = ASTNodeType::COMPONENT;
    chipset->children = new std::vector<t_ast_node *>();

    std::string name;
    inputChar = m_str.peek();

    if (inputChar == 't')
      {
	// name should be "true"
	char nameBuf[5];

	m_str.get(nameBuf, 4);
	name = std::string(nameBuf);

	if (name != "true")
	  {
	    throw new std::exception(); // TODO: create specific exception
	  }
      }
    else if (inputChar == 'f')
      {
	// name should be "false"
	char nameBuf[6];

	m_str.get(nameBuf, 5);
	name = std::string(nameBuf);

	if (name != "false")
	  {
	    throw new std::exception(); // TODO: create specific exception
	  }
      }
    else
      {
	// name should be "output"
	char nameBuf[7];

	m_str.get(nameBuf, 6);
	name = std::string(nameBuf);

	if (name != "output")
	  {
	    throw new std::exception(); // TODO: create specific exception
	  }
      }
    chipset->lexeme += name;
    chipset->value += name;

    inputChar = m_str.peek();
    if (inputChar != ' ' && inputChar != '\t')
      {
	throw new std::exception(); // TODO: create specific exception
      }

    while (true)
      {
	inputChar = m_str.peek();
	switch (inputChar)
	  {
	  case ' ':
	  case '\t':
	    break;
	  case '\n':
	    throw new std::exception(); // TODO: create specific exception
	  default:
	    chipset->children->push_back(this->createTreeString());
	    return (chipset);
	  }
      }
  }
}