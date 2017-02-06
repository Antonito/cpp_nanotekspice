#include <iostream>
#include <stdexcept>
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

  void Parser::feed(std::string const &input)
  {
    m_str << input;
  }

  void Parser::parseTree(t_ast_node &root)
  {
    bool chipset = false;
    bool link = false;

    for (t_ast_node *child : *root.children)
      {
	switch (child->type)
	  {
	  case ASTNodeType::NEWLINE:
	    break;
	  case ASTNodeType::SECTION:
	    if (child->value == "chipsets")
	      {
		if (chipset)
		  {
		    throw LexicalOrSyntacticError(
		        "Multiple .chipsets section");
		  }
		this->parseChipsets(*child);
		chipset = true;
	      }
	    else if (child->value == "links")
	      {
		if (link)
		  {
		    throw LexicalOrSyntacticError("Multiple .links section");
		  }
		if (!chipset)
		  {
		    throw LexicalOrSyntacticError(
		        ".links section before ./chipsets section");
		  }
		this->parseLinks(*child);
		link = true;
	      }
	    break;
	  default:
	    throw LexicalOrSyntacticError("Lexical or syntaxic error");
	  }
      }
    if (!chipset || !link)
      {
	throw LexicalOrSyntacticError(
	    "chipset or link section (or both) is missing");
      }
  }

  void Parser::parseChipsets(t_ast_node &section)
  {
    for (t_ast_node *child : *section.children)
      {
	switch (child->type)
	  {
	  case ASTNodeType::NEWLINE:
	    break;
	  case ASTNodeType::COMPONENT:
	    this->parseComponent(*child);
	    break;
	  default:
	    throw LexicalOrSyntacticError("Lexical or syntaxic error");
	  }
      }
  }

  void Parser::parseLinks(t_ast_node &section)
  {
    for (t_ast_node *child : *section.children)
      {
	switch (child->type)
	  {
	  case ASTNodeType::NEWLINE:
	    break;
	  case ASTNodeType::LINK:
	    this->parseLink(*child);
	    break;
	  default:
	    throw LexicalOrSyntacticError("Lexical or syntaxic error");
	  }
      }
  }

  void Parser::parseComponent(t_ast_node &component)
  {
    std::string type = component.value;
    std::string name;
    std::string value;

    for (t_ast_node *child : *component.children)
      {
	switch (child->type)
	  {
	  case ASTNodeType::NEWLINE:
	    break;
	  case ASTNodeType::STRING:
	    if (name == "")
	      name = child->value;
	    else if (value == "")
	      value = child->value;
	    else
	      throw LexicalOrSyntacticError("Lexical or syntaxic error");
	    break;
	  default:
	    throw LexicalOrSyntacticError("Lexical or syntaxic error");
	  }
      }

    if (m_input.find(name) != m_input.end() ||
        m_component.find(name) != m_component.end() ||
        m_output.find(name) != m_output.end())
      {
	throw LexicalOrSyntacticError("Several component share the same name");
      }

    if (type == "input")
      {
	m_input[name] = std::make_shared<Input>(Input::INPUT, value);
      }
    else if (type == "clock")
      {
	m_input[name] = std::make_shared<Input>(Input::CLOCK, value);
      }
    else if (type == "output")
      {
	if (value != "")
	  throw LexicalOrSyntacticError("An output cannot have a value");
	m_output[name].first = std::make_shared<Output>();
	m_output[name].second = false;
      }
    else
      {
	m_component[name] = std::shared_ptr<IComponent>(
	    m_compFactory.createComponent(type, value));
      }
  }

  void Parser::parseLink(t_ast_node &link)
  {
    std::pair<IComponent *, size_t> end[2];
    int n = 0;

    for (t_ast_node *child : *link.children)
      {
	switch (child->type)
	  {
	  case ASTNodeType::NEWLINE:
	    break;
	  case ASTNodeType::LINK_END:
	    if (n > 1)
	      throw LexicalOrSyntacticError("Lexical or syntaxic error");

	    end[n] = this->parseLinkEnd(*child);
	    n++;
	    break;
	  default:
	    throw LexicalOrSyntacticError("Lexical or syntaxic error");
	  }
      }

    if (n != 2)
      throw LexicalOrSyntacticError("Lexical or syntaxic error");

    try
      {
	end[0].first->SetLink(end[0].second, *end[1].first, end[1].second);
      }
    catch (std::exception &)
      {
	end[1].first->SetLink(end[1].second, *end[0].first, end[0].second);
      }
  }

  std::pair<IComponent *, size_t> Parser::parseLinkEnd(t_ast_node &link)
  {
    std::pair<IComponent *, size_t> res;
    std::string val;
    std::string name = link.value;

    for (t_ast_node *child : *link.children)
      {
	switch (child->type)
	  {
	  case ASTNodeType::NEWLINE:
	    break;
	  case ASTNodeType::STRING:
	    if (val != "")
	      throw LexicalOrSyntacticError("Lexical or syntaxic error");
	    val = child->value;
	    break;
	  default:
	    throw LexicalOrSyntacticError("Lexical or syntaxic error");
	  }
      }

    if (m_input.find(name) != m_input.end())
      res.first = m_input[name].get();
    else if (m_component.find(name) != m_component.end())
      res.first = m_component[name].get();
    else if (m_output.find(name) != m_output.end())
      {
	res.first = m_output[name].first.get();
	m_output[name].second = true;
      }
    else
      throw LexicalOrSyntacticError("A component name is unknown");

    for (char c : val)
      if (std::isdigit(c) == false)
	throw LexicalOrSyntacticError("Lexical or syntaxic error");
    res.second = std::atoi(val.c_str());
    return (res);
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
	        "Invalid character in root"); // TODO: create specific
	                                      // exception
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
	    "Section name beggining with unknown character"); // TODO: create
	                                                      // specific
	                                                      // exception
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
	    "' instead of 'chipsets'"); // TODO: create specific exception
      }

    section->lexeme += name;
    section->value = name;

    // Check that it is followed by a ':'
    inputChar = m_str.get();
    if (inputChar != ':')
      {
	throw LexicalOrSyntacticError(
	    "Missing ':' after '.chipsets'"); // TODO: create specific
	                                      // exception
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
	    "' instead of 'links'"); // TODO: create specific exception
      }

    section->lexeme += name;
    section->value = name;

    // Check that it is followed by a ':'
    inputChar = m_str.get();
    if (inputChar != ':')
      {
	throw LexicalOrSyntacticError(
	    "Missing ':' after '.links'"); // TODO: create specific exception
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
	        "Unexpected EOF in link creation"); // TODO: create specific
	                                            // exception
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
	        "Unexpected EOF in link_end creation (1)"); // TODO: create
	                                                    // specific
	                                                    // exception
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
	        "Unexpected character in link_end creation"); // TODO: create
	                                                      // specific
	                                                      // exception
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
	        "Unexpected EOF in link_end creation (2)"); // TODO: create
	                                                    // specific
	                                                    // exception
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
	    "Missing space or tab after input chipset type"); // TODO: create
	                                                      // specific
	                                                      // exception
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
	        "Unexpected EOL in input chipset creation"); // TODO: create
	                                                     // specific
	                                                     // exception
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
		    "Missing ')' after input chipset value declaration"); // TODO:
		// create
		// specific
		// exception
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

  std::map<std::string, std::shared_ptr<Input>> const &Parser::getInput() const
  {
    return (m_input);
  }

  std::map<std::string, std::shared_ptr<IComponent>> const &
      Parser::getComponent() const
  {
    return (m_component);
  }

  std::map<std::string, std::shared_ptr<Output>> Parser::getOutput() const
  {
    std::map<std::string, std::shared_ptr<Output>> res;

    for (auto &e : m_output)
      {
	if (e.second.second == false)
	  throw InvalidInput("Not every output is linked");
	res[e.first] = e.second.first;
      }
    return (res);
  }
}