#include <fstream>
#include <sstream>
#include <iostream>
#include <csignal>
#include "ComponentFactory.hpp"
#include "Simulator.hpp"
#include "BadParameter.hpp"
#include "InvalidInput.hpp"
#include "UnknownComponent.hpp"
#include "Parser.hpp"
#pragma message("REMOVE THOSE AUTOs")
namespace nts
{
  bool   Simulator::m_looping = false;
  size_t Simulator::m_simId = 0;

  void Simulator::loopingSignal(int sig)
  {
    if (sig == SIGINT)
      Simulator::m_looping = false;
  }

  Simulator::Simulator(t_ast_node &root, char *param[], size_t n)
  {
	this->init(root);

	for (size_t i = 0; i < n; ++i)
	  this->setInput(std::string(param[i]), true);

	Simulator::m_simId++;
	for (auto &i : m_input)
	  if (i.second->Compute() == nts::UNDEFINED)
	    {
	      std::cout << i.first << std::endl;
	      throw InvalidInput("Missing input value on command line");
	    }

	signal(SIGINT, &Simulator::loopingSignal);
	this->simulate();
	this->display();
  }

  Simulator::~Simulator()
  {
  }

  void Simulator::simulate()
  {
    Simulator::m_simId++;
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
	std::cout << i.first << "=";
	switch (i.second->getLastValue())
	  {
	  case nts::TRUE:
	    std::cout << "1";
	    break;
	  case nts::FALSE:
	    std::cout << "0";
	    break;
	  default:
	    std::cout << "U";
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

  size_t Simulator::simId()
  {
    return (Simulator::m_simId);
  }

  void Simulator::init(t_ast_node &root)
  {
	  for (t_ast_node *n : *root.children)
	  {
		  if (n->type == ASTNodeType::SECTION)
		  {
			  if (n->value[0] == 'c')
			  {
				  this->initChipsets(*n);
			  }
			  else
			  {
				  this->initLinks(*n);
			  }
		  }
	  }
  }

  void Simulator::initChipsets(t_ast_node &section)
  {
	  for (t_ast_node *n : *section.children)
	  {
		  if (n->type == ASTNodeType::COMPONENT)
		  {
			  this->initComponent(*n);
		  }
	  }
  }

  void Simulator::initLinks(t_ast_node &section)
  {
	  for (t_ast_node *n : *section.children)
	  {
		  if (n->type == ASTNodeType::LINK)
		  {
			  this->initLink(*n);
		  }
	  }
  }

  void Simulator::initComponent(t_ast_node &comp)
  {
	  int s = 0;
	  std::string val[2];

	  for (t_ast_node *n : *comp.children)
	  {
		  if (n->type == ASTNodeType::STRING)
		  {
			  val[s] = n->value;
			  ++s;
		  }
	  }
	  if (comp.value == "input")
	  {
		  m_input[val[0]] = std::make_unique<Input>(Input::INPUT, val[1]);
	  }
	  else if (comp.value == "clock")
	  {
		  m_input[val[0]] = std::make_unique<Input>(Input::CLOCK, val[1]);
	  }
	  else if (comp.value == "output")
	  {
		  m_output[val[0]] = std::make_unique<Output>();
	  }
	  else
	  {
		  m_component[val[0]] = std::unique_ptr<IComponent>(m_factory.createComponent(comp.value, val[1]));
	  }
  }

  void Simulator::initLink(t_ast_node &link)
  {
	  std::pair<IComponent *, int> ends[2];
	  int e = 0;

	  for (t_ast_node *n : *link.children)
	  {
		  if (n->type == ASTNodeType::LINK_END)
		  {
			  ends[e] = this->initLinkEnd(*n);
			  ++e;
		  }
	  }
	  ends[0].first->SetLink(ends[0].second, *ends[1].first, ends[1].second);
	  ends[1].first->SetLink(ends[1].second, *ends[0].first, ends[0].second);
  }

  std::pair<IComponent *, int> Simulator::initLinkEnd(t_ast_node &end)
  {
	  std::pair<IComponent *, int> link;

	  for (t_ast_node *n: *end.children)
	  {
		  if (n->type == ASTNodeType::STRING)
		  {
			  link.second = std::stoi(n->value);
		  }
	  }
	  if (m_input.count(end.value))
	  {
		  link.first = m_input[end.value].get();
	  }
	  else if (m_component.count(end.value))
	  {
		  link.first = m_component[end.value].get();
	  }
	  else
	  {
		  link.first = m_output[end.value].get();
	  }
	  return (link);
  }
}