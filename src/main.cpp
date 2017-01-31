#include <iostream>
#include "Simulator.hpp"

#define TRYIT_

int main(int ac, char **av)
{

  if (ac == 1)
    std::cerr << av[0] << " CONFIG_FILE [INPUT=(0|1)] ..." << std::endl;

#ifdef TRYIT
  try
    {
#endif
      nts::Simulator simulator(av[1], &av[2], ac - 2);
      std::string    command;

      std::cout << ">" << std::flush;
      while (getline(std::cin, command))
	{
	  if (simulator.command(command) == false)
	    break;
	  std::cout << ">" << std::flush;
	}
#ifdef TRYIT
    }
  catch (std::exception &e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
      return (1);
    }
#endif
  return (0);
}