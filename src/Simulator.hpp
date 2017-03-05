#ifndef SIMULATOR_HPP_
#define SIMULATOR_HPP_

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "IComponent.hpp"
#include "cpp_nanoTekSpice_parser.hpp"
#include "ComponentFactory.hpp"

namespace nts
{
  class Input;
  class Output;

  class Simulator
  {
  public:
    explicit Simulator(t_ast_node &root, char *param[], size_t n);
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

	void init(t_ast_node &root);
	void initChipsets(t_ast_node &section);
	void initLinks(t_ast_node &section);
	void initComponent(t_ast_node &comp);
	void initLink(t_ast_node &link);
	std::pair<IComponent *, int> initLinkEnd(t_ast_node &end);

    std::map<std::string, std::unique_ptr<Input>>      m_input;
    std::map<std::string, std::unique_ptr<IComponent>> m_component;
    std::map<std::string, std::unique_ptr<Output>>     m_output;
	ComponentFactory m_factory;
    static bool   m_looping;
    static size_t m_simId;
  };
}

#endif // !SIMULATOR_HPP_