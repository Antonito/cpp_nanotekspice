#include <fstream>
#include <sstream>
#include <iostream>
#include <csignal>
#include "Simulator.hpp"
#include "BadParameter.hpp"
#include "InvalidInput.hpp"
#include "UnknownComponent.hpp"

namespace nts
{
  bool Simulator::m_looping = false;

  void Simulator::loopingSignal(int sig)
  {
    if (sig == SIGINT)
      Simulator::m_looping = false;
  }

  Simulator::Simulator(char const *fileName, char *param[], size_t n)
  {
    std::ifstream file(fileName);

    if (file.is_open())
      {
	Parser            parser;
	std::stringstream ss;

	ss << file.rdbuf();

	parser.feed(ss.str());
	file.close();

	nts::t_ast_node *root = parser.createTree();

	parser.parseTree(*root);
	m_input = parser.getInput();
	m_component = parser.getComponent();
	m_output = parser.getOutput();

	for (size_t i = 0; i < n; ++i)
	  this->setInput(std::string(param[i]), true);

	for (auto &i : m_input)
	  if (i.second->Compute() == nts::UNDEFINED)
	    throw InvalidInput("Missing input value on command line");

	signal(SIGINT, &Simulator::loopingSignal);
      }
    else
      {
	throw BadParameter("Invalid file name");
      }
  }

  Simulator::~Simulator()
  {
    for (auto &i : m_input)
      delete i.second;
    for (auto &i : m_component)
      delete i.second;
    for (auto &i : m_output)
      delete i.second;
  }

  void Simulator::simulate()
  {
    for (auto &i : m_output)
      i.second->getValue();
    for (auto &i : m_input)
      i.second->update();
  }

  void Simulator::dump() const
  {
    for (auto &i : m_input)
      {
	std::cout << i.first << " ";
	i.second->Dump();
      }
    for (auto &i : m_component)
      {
	std::cout << i.first << " ";
	i.second->Dump();
      }
    for (auto &i : m_output)
      {
	std::cout << i.first << " ";
	i.second->Dump();
      }
  }

  void Simulator::setInput(std::string const &command, bool set)
  {
    std::string name;
    Tristate    value = nts::UNDEFINED;
    size_t      i = 0;

    while (command[i] != '=')
      {
	if (i == command.size())
	  throw InvalidInput("Bad input initialization");
	name += command[i];
	i++;
      }
    if (command.size() - i != 2 || command[i] != '=')
      throw InvalidInput("Bad input initialization");

    i++;
    if (command[i] == '1')
      value = nts::TRUE;
    else if (command[i] == '0')
      value = nts::FALSE;
    else
      throw InvalidInput("The value must be 0 or 1");

    if (m_input.find(name) == m_input.end())
      throw UnknownComponent("This input component cannot be found");
    if (set)
      m_input[name]->setValue(value);
    else
      m_input[name]->changeValue(value);
  }

  void Simulator::display() const
  {
    for (auto &i : m_output)
      {
	std::cout << i.first << " = ";
	switch (i.second->getLastValue())
	  {
	  case nts::TRUE:
	    std::cout << "TRUE";
	    break;
	  case nts::FALSE:
	    std::cout << "FALSE";
	    break;
	  default:
	    std::cout << "UNDEFINED";
	    break;
	  }
	std::cout << std::endl;
      }
  }

  bool Simulator::command(std::string const &c)
  {
    if (c == "exit")
      return (false);
    else if (c == "display")
      this->display();
    else if (c == "simulate")
      this->simulate();
    else if (c == "dump")
      this->dump();
    else if (c == "loop")
      {
	m_looping = true;
	while (m_looping)
	  this->simulate();
	std::cout << std::endl;
      }
    else
      this->setInput(c);

    return (true);
  }
}