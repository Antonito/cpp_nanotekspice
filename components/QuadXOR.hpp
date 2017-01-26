#ifndef QUADXOR_HPP_
#define QUADXOR_HPP_

#include "AQuadSimple.hpp"

namespace nts
{
  class QuadXOR : public AQuadSimple
  {
  public:
    QuadXOR();
    virtual ~QuadXOR();

  private:
    virtual nts::Tristate operation(nts::Tristate, nts::Tristate) const = 0;
  };
}

#endif // !QUADXOR_HPP_