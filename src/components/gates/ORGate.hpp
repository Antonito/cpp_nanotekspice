#ifndef ORGATE_HPP_
#define ORGATE_HPP_

#include "AGate.hpp"

namespace nts
{
  class ORGate : public AGate
  {
  public:
    ORGate();
    virtual ~ORGate(){};

    virtual nts::Tristate doOperation();
  };
}

#endif // !ORGATE_HPP_