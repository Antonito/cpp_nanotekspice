#ifndef NORGATE_HPP_
#define NORGATE_HPP_

#include "AGate.hpp"

namespace nts
{
  class NORGate : public AGate
  {
  public:
    NORGate();
    virtual ~NORGate(){};

    virtual nts::Tristate doOperation();
  };
}

#endif // !NORGATE_HPP_