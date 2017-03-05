#include <iostream>
#include <fstream>
#include "Simulator.hpp"
#include "BadParameter.hpp"
#include "Parser.hpp"

#define TRYIT_

int main(int ac, char **av)
{

  if (ac == 1)
    {
      std::cerr << av[0] << " CONFIG_FILE [INPUT=(0|1)] ..." << std::endl;
      return (1);
    }

#ifdef TRYIT
  try
    {
#endif
      std::ifstream file(av[1]);

      if (file.is_open() == false)
	{
	  throw nts::BadParameter("Invalid file name");
	}

      nts::Parser            parser;
      std::stringstream ss;

      ss << file.rdbuf();

      parser.feed(ss.str());
      file.close();

      nts::t_ast_node *root = parser.createTree();

      parser.parseTree(*root);

      nts::Simulator simulator(*root, &av[2], ac - 2);
      parser.deleteTree(root);

      std::string command;

      std::cout << "> " << std::flush;
      while (getline(std::cin, command))
	{
	  try
	    {
	      if (simulator.command(command) == false)
		break;
	    }
	  catch (std::exception &e)
	    {
	      std::cerr << e.what() << std::endl;
	    }
	  std::cout << "> " << std::flush;
	}
#ifdef TRYIT
    }
  catch (std::exception &e)
    {
      std::cerr << "Fatal error: " << e.what() << std::endl;
      return (1);
    }
#endif
  return (0);
}
