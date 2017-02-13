#ifndef SIXNOT_HPP_
#define SIXNOT_HPP_

#include <string>
#include "Component.hpp"
#include "NOTGate.hpp"

namespace nts
{
  class SixNot : public Component<14>
  {
  public:
    SixNot(std::string const &type);
    virtual ~SixNot(){};

  private:
    NOTGate m_gates[6];
  };
}

#endif // !SIXNOT_HPP_