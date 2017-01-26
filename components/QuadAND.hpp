#ifndef QUADAND_HPP_
#define QUADAND_HPP_

#include "AQuadSimple.hpp"

namespace nts
{
  class QuadAND : public AQuadSimple
  {
  public:
    QuadAND();
    virtual ~QuadAND();

  private:
    virtual nts::Tristate operation(nts::Tristate, nts::Tristate) const = 0;
  };
}

#endif // !QUADAND_HPP_