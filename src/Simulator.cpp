#include "Simulator.hpp"

namespace nts
{
  Simulator::Simulator(std::string const &fileName)
  {
    std::ifstream file(fileName.c_str());

    if (file.is_open())
      {
	Parser            parser;
	std::stringstream ss = file.rdbuf();

	parser.feed(ss.str());
	file.close();

	nts::t_ast_node *root = parser.createTree();

	parser.parseTree(*root);
	m_input = parser.getInput();
	m_chipsets = parser.getChipsets();
	m_output = parser.getOutput();
      }
    else
      {
	throw std::logic_error("Invalid file name");
      }
  }

  Simulator::Simulator(Simulator const &other)
  {
  }

  Simulator::~Simulator()
  {
  }

  Simulator &Simulator::operator=(Simulator const &other)
  {
    if (this != &other)
      {
      }
    return (*this);
  }
}