#ifndef XORGATE_HPP_
#define XORGATE_HPP_

#include "AGate.hpp"

namespace nts
{
  class XORGate : public AGate
  {
  public:
    XORGate();
    virtual ~XORGate(){};

    virtual void doOperation();
  };
}

#endif // !XORGATE_HPP_