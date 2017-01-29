#include "Simulator.hpp"

int main(int ac, char **av)
{
  if (ac == 1)
    throw std::logic_error("No file given as parameter");
  nts::Simulator simulator(av[1], &av[2], ac - 2);
  std::string    command;

  std::cout << ">" << std::flush;
  while (getline(std::cin, command))
    {
      if (simulator.command(command) == false)
	break;
      std::cout << ">" << std::flush;
    }
  return 0;
}