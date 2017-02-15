#include <iostream>
#include "Simulator.hpp"

#define TRYIT

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
      nts::Simulator simulator(av[1], &av[2], ac - 2);
      std::string    command;

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
