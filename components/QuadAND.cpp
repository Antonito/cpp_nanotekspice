#include "QuadAND.hpp"

namespace nts
{
  QuadAND::QuadAND() : AQuadSimple("4001 (4 NOR)")
  {
  }

  QuadAND::~QuadAND()
  {
  }

  nts::Tristate QuadAND::operation(nts::Tristate a, nts::Tristate b) const
  {
    return (static_cast<nts::Tristate>(static_cast<bool>(a) &&
                                       static_cast<bool>(b)));
  }
}