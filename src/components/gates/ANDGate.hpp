#ifndef ANDGATE_HPP_
#define ANDGATE_HPP_

#include "AGate.hpp"

namespace nts
{
  class ANDGate : public AGate
  {
  public:
    ANDGate();
    virtual ~ANDGate(){};

    virtual void doOperation();
  };
}

#endif // !ANDGATE_HPP_