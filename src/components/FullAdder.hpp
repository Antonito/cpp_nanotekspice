#ifndef FULLADDER_HPP_
#define FULLADDER_HPP_

#include <string>
#include "Component.hpp"
#include "IOperable.hpp"
#include "Gates.hpp"

namespace nts
{
  class FullAdder : public Component<5>
  {
  public:
    FullAdder(std::string const &type = "Full Adder");
    virtual ~FullAdder();

  private:
    NodeGate m_node[3];
    ANDGate  m_and[2];
    ORGate   m_or;
    XORGate  m_xor[2];
  };
}

#endif // !FULLADDER_HPP_