#include "QuadOR.hpp"

namespace nts
{
  QuadOR::QuadOR() : AQuadSimple("4001 (4 NOR)")
  {
  }

  QuadOR::~QuadOR()
  {
  }

  nts::Tristate QuadOR::operation(nts::Tristate a, nts::Tristate b) const
  {
    return (static_cast<nts::Tristate>(static_cast<bool>(a) ||
                                       static_cast<bool>(b)));
  }
}