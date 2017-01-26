#include "QuadXOR.hpp"

namespace nts
{
  QuadXOR::QuadXOR() : AQuadSimple("4001 (4 NOR)")
  {
  }

  QuadXOR::~QuadXOR()
  {
  }

  nts::Tristate QuadXOR::operation(nts::Tristate a, nts::Tristate b) const
  {
    return (static_cast<nts::Tristate>(a != b));
  }
}