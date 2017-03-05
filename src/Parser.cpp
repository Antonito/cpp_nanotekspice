#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "LexicalOrSyntacticError.hpp"
#include "Parser.hpp"
#include "Output.hpp"
#include "InvalidInput.hpp"

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

  void Parser::deleteTree(t_ast_node *root) const
  {
    if (root->children != nullptr)
      {
	for (t_ast_node *child : *root->children)
	  {
	    this->deleteTree(child);
	  }
	delete root->children;
      }
    delete root;
  }

  void Parser::feed(std::string const &input)
  {
    m_str << input;
  }

  void Parser::parseTree(t_ast_node &root)
  {
    int s = 0;

    for (t_ast_node *n : *root.children)
      {
	if (n->type == ASTNodeType::SECTION)
	  {
	    if (this->parseSection(*n) != s)
	      {
		throw LexicalOrSyntacticError("Invalid section order");
	      }
	    ++s;
	  }
	else if (n->type != ASTNodeType::NEWLINE)
	  {
	    throw LexicalOrSyntacticError("Invalid element");
	  }
      }
  }

  int Parser::parseSection(t_ast_node &section)
  {
    if (section.value == "chipsets")
      {
	this->parseChipsets(section);
	return 0;
      }
    else if (section.value == "links")
      {
	this->parseLinks(section);
	return 1;
      }
    else
      {
	throw LexicalOrSyntacticError("Invalid section name");
      }
  }

  void Parser::parseChipsets(t_ast_node &section)
  {
    for (t_ast_node *n : *section.children)
      {
	if (n->type == ASTNodeType::COMPONENT)
	  {
	    this->parseComponent(*n);
	  }
	else if (n->type != ASTNodeType::NEWLINE)
	  {
	    throw LexicalOrSyntacticError(
	        "Invalid element in chipsets section");
	  }
      }
  }

  void Parser::parseLinks(t_ast_node &section)
  {
    for (t_ast_node *n : *section.children)
      {
	if (n->type == ASTNodeType::LINK)
	  {
	    this->parseLink(*n);
	  }
	else if (n->type != ASTNodeType::NEWLINE)
	  {
	    throw LexicalOrSyntacticError("Invalid element in links section");
	  }
      }
  }

  void Parser::parseComponent(t_ast_node &component)
  {
	  std::string val[2];
	  int s = 0;

    for (t_ast_node *n : *component.children)
      {
		if (s > 2)
		{
			throw LexicalOrSyntacticError("Invalid component definition");
		}
	if (n->type == ASTNodeType::STRING)
	  {
		val[s] = n->value;
	    s++;
	  }

	else
	  {
	    throw LexicalOrSyntacticError(
	        "Invalid element in component definition");
	  }
      }

    if (s < 1)
      {
	throw LexicalOrSyntacticError(
	    "Invalid component definition (missing name)");
      }

    if (std::find(m_component.begin(), m_component.end(), val[0]) !=
        m_component.end())
      {
		throw LexicalOrSyntacticError(
			"There are more than one component with name '" + val[0] + "'");
      }

    if (component.value == "output")
      {
	m_output[val[0]] = false;
      }
    m_component.push_back(val[0]);
  }

  void Parser::parseLink(t_ast_node &link)
  {
    int l = 0;

    for (t_ast_node *n : *link.children)
      {
	if (n->type == ASTNodeType::LINK_END)
	  {
	    this->parseLinkEnd(*n);
	    ++l;
	  }
	else
	  {
	    throw LexicalOrSyntacticError("Invalid link definition");
	  }
      }
    if (l != 2)
      {
	throw LexicalOrSyntacticError("Invalid link definition");
      }
  }

  void Parser::parseLinkEnd(t_ast_node &end)
  {
    std::string pin;
    int         p = 0;

    for (t_ast_node *n : *end.children)
      {
	if (n->type == ASTNodeType::STRING)
	  {
	    pin = n->value;
	    ++p;
	  }
	else
	  {
	    throw LexicalOrSyntacticError("Invalid link end definition");
	  }
      }
    if (std::find(m_component.begin(), m_component.end(), end.value) ==
        m_component.end())
      {
	throw LexicalOrSyntacticError("Unknown component '" + end.value +
	                              "' in link definition");
      }
    if (m_output.find(end.value) != m_output.end())
      {
	m_output[end.value] = true;
      }
  }

  //
  // Entry point of the parsing
  //

  t_ast_node *Parser::createTree()
  {
    t_ast_node *root = new t_ast_node(nullptr);
    char        inputChar;

    // Node creation
    root->type = ASTNodeType::DEFAULT;
    root->children = new std::vector<t_ast_node *>();
    root->lexeme = m_str.str();

    this->clearInput();

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
	    throw LexicalOrSyntacticError(
	        "Invalid character in root");
	    break;
	  }
      }
  }

  t_ast_node *Parser::createTreeSection(char inputChar)
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
	throw LexicalOrSyntacticError(
	    "Section name beggining with unknown character");
      }
  }

  t_ast_node *Parser::createTreeNewline(char inputChar)
  {
    t_ast_node *newline = new t_ast_node(nullptr);

    // Node creation
    newline->type = ASTNodeType::NEWLINE;
    newline->children = nullptr;
    newline->lexeme += inputChar;
    newline->value += inputChar;

    return (newline);
  }

  t_ast_node *Parser::createTreeChipsetsSection(char inputChar)
  {
    t_ast_node *section = new t_ast_node(nullptr);

    // Node creation
    section->type = ASTNodeType::SECTION;
    section->children = new std::vector<t_ast_node *>();
    section->lexeme += inputChar;

    // Get the name (must be "chipsets")
    char nameBuf[9];
    m_str.get(nameBuf, 9);
    std::string name(nameBuf);

    // Check if the section name is good
    if (name != "chipsets")
      {
	throw LexicalOrSyntacticError(
	    std::string("Section name is '") + name +
	    "' instead of 'chipsets'");
      }

    section->lexeme += name;
    section->value = name;

    // Check that it is followed by a ':'
    inputChar = m_str.get();
    if (inputChar != ':')
      {
	throw LexicalOrSyntacticError(
	    "Missing ':' after '.chipsets'");
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

  t_ast_node *Parser::createTreeLinksSection(char inputChar)
  {
    t_ast_node *section = new t_ast_node(nullptr);

    // Node creation
    section->type = ASTNodeType::SECTION;
    section->children = new std::vector<t_ast_node *>();
    section->lexeme += inputChar;

    // Get the name (must be "links")
    char nameBuf[6];
    m_str.get(nameBuf, 6);
    std::string name(nameBuf);

    // Check if the section name is good
    if (name != "links")
      {
	throw LexicalOrSyntacticError(
	    std::string("Section name is '") + name +
	    "' instead of 'links'");
      }

    section->lexeme += name;
    section->value = name;

    // Check that it is followed by a ':'
    inputChar = m_str.get();
    if (inputChar != ':')
      {
	throw LexicalOrSyntacticError(
	    "Missing ':' after '.links'");
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
	    m_str.get();
	    break;
	  // Chipset
	  default:
	    section->children->push_back(this->createTreeLink());
	    break;
	  }
      }
  }

  t_ast_node *Parser::createTreeLink()
  {
    t_ast_node *link = new t_ast_node(nullptr);
    char        inputChar;
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
	    m_str.get();
	    break;
	  case '\n':
	    link->children->push_back(this->createTreeNewline(m_str.get()));
	    break;
	  case EOF:
	    throw LexicalOrSyntacticError(
	        "Unexpected EOF in link creation");
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
    char        inputChar;

    // Node creation
    end->type = ASTNodeType::LINK_END;
    end->children = new std::vector<t_ast_node *>();

    // Get name
    while (true)
      {
	inputChar = m_str.get();

	if (inputChar == EOF)
	  {
	    throw LexicalOrSyntacticError(
	        "Unexpected EOF in link_end creation (1)");
	  }

	if (inputChar == ':')
	  {
	    break;
	  }
	if (std::isalnum(inputChar) || inputChar == '_')
	  {
	    end->lexeme += inputChar;
	    end->value += inputChar;
	  }
	else
	  {
	    throw LexicalOrSyntacticError(
	        "Unexpected character in link_end creation");
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
	    throw LexicalOrSyntacticError(
	        "Unexpected EOF in link_end creation (2)");
	  default:
	    end->children->push_back(this->createTreeString());
	    return (end);
	  }
      }
  }

  t_ast_node *Parser::createTreeString()
  {
    t_ast_node *str = new t_ast_node(nullptr);
    char        inputChar;

    // Node creation
    str->type = ASTNodeType::STRING;
    str->children = nullptr;

    while (true)
      {
	inputChar = m_str.peek();
	if (std::isalnum(inputChar) || inputChar == '_')
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

  t_ast_node *Parser::createTreeChipset()
  {
    t_ast_node *chipset = new t_ast_node(nullptr);
    char        inputChar;

    // Node creation
    chipset->type = ASTNodeType::COMPONENT;
    chipset->children = new std::vector<t_ast_node *>();

    while (true)
      {
	inputChar = m_str.peek();
	if (std::isalnum(inputChar))
	  {
	    chipset->lexeme += inputChar;
	    chipset->value += inputChar;
	    m_str.get();
	  }
	else
	  break;
      }

    inputChar = m_str.peek();
    if (inputChar != ' ' && inputChar != '\t')
      {
	throw LexicalOrSyntacticError(
	    "Missing space or tab after input chipset type");
      }

    bool gettingName = true;
    while (gettingName)
      {
	inputChar = m_str.peek();
	switch (inputChar)
	  {
	  case ' ':
	  case '\t':
	    m_str.get();
	    break;
	  case '\n':
	    throw LexicalOrSyntacticError(
	        "Unexpected EOL in input chipset creation");
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
	    m_str.get();
	    break;
	  case '\n':
	    return (chipset);
	  case '(':
	    m_str.get();
	    chipset->children->push_back(this->createTreeString());
	    inputChar = m_str.get();
	    if (inputChar != ')')
	      {
		throw LexicalOrSyntacticError(
		    "Missing ')' after input chipset value declaration");
	      }
	    return (chipset);
	  default:
	    throw LexicalOrSyntacticError("Unknown character");
	  }
      }
  }

  void Parser::clearInput()
  {
    char              inputChar;
    char              lastChar = 0;
    std::stringstream clear;

    while (true)
      {
	inputChar = m_str.get();
	if (inputChar == EOF)
	  {
	    break;
	  }

	if (inputChar == '#')
	  {
	    while (inputChar != EOF && inputChar != '\n')
	      inputChar = m_str.get();
	    clear << '\n';
	  }
	else if ((inputChar != ' ' && inputChar != '\t') ||
	         (lastChar != ' ' && lastChar != '\t'))
	  {
	    clear << inputChar;
	  }
	lastChar = inputChar;
      }
    m_str.str("");
    m_str.clear();
    m_str << clear.str();
  }
}