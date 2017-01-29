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
    explicit Simulator(char const *fileName, char *param[], size_t n);
    Simulator(Simulator const &other) = delete;
    ~Simulator();
    Simulator &operator=(Simulator const &other) = delete;

    bool command(std::string const &c);
    static void loopingSignal(int sig);

  private:
    void simulate();
    void dump() const;
    void setInput(std::string const &command);
    void display() const;

    std::map<std::string, Input *>      m_input;
    std::map<std::string, IComponent *> m_component;
    std::map<std::string, Output *>     m_output;
    static bool m_looping;
  };
}

#endif // !SIMULATOR_HPP_