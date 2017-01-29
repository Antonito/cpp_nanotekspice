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
    Simulator(Simulator const &other) = delete;
    ~Simulator();
    Simulator &operator=(Simulator const &other) = delete;

  private:
    std::map<std::string, Input *>      m_input;
    std::map<std::string, IComponent *> m_component;
    std::map<std::string, IComponent *> m_output;
  };
}

#endif // !SIMULATOR_HPP_