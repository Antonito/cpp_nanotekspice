#ifndef SIMULATOR_HPP_
#define SIMULATOR_HPP_

#include <vector>
#include <map>
#include <string>
#include "Parser.hpp"
#include "IComponent.hpp"

namespace nts
{
  class Simulator
  {
  public:
    explicit Simulator(std::string const &configFileName);
    ~Simulator();

  private:
    Simulator(Simulator const &other);
    Simulator &operator=(Simulator const &other);

    std::map<std::string, InputComponent *> m_input;
    std::vector<IComponent *> m_chipsets;
    std::map<std::string, IComponent *> m_output;
  };
}

#endif // !SIMULATOR_HPP_