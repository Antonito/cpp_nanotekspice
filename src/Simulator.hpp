#ifndef SIMULATOR_HPP_
#define SIMULATOR_HPP_

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "IComponent.hpp"

namespace nts
{
  class Input;
  class Output;

  class Simulator
  {
  public:
    explicit Simulator(char const *fileName, char *param[], size_t n);
    Simulator(Simulator const &other) = delete;
    ~Simulator();
    Simulator &operator=(Simulator const &other) = delete;

    bool command(std::string const &c);
    static void loopingSignal(int sig);
    static size_t simId();

  private:
    void simulate();
    void dump() const;
    void setInput(std::string const &command, bool set = false);
    void display() const;

    std::map<std::string, std::shared_ptr<Input>>      m_input;
    std::map<std::string, std::shared_ptr<IComponent>> m_component;
    std::map<std::string, std::shared_ptr<Output>>     m_output;
    static bool   m_looping;
    static size_t m_simId;
  };
}

#endif // !SIMULATOR_HPP_