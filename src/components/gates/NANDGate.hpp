#ifndef NANDGATE_HPP_
#define NANDGATE_HPP_

#include "AGate.hpp"

namespace nts
{
  class NANDGate : public AGate
  {
  public:
    NANDGate();
    virtual ~NANDGate(){};

    virtual nts::Tristate doOperation();
  };
}

#endif // !NANDGATE_HPP_