#include "QuadNAND.hpp"

namespace nts
{
  QuadNAND::QuadNAND() : AQuadSimple("4001 (4 NOR)")
  {
  }

  QuadNAND::~QuadNAND()
  {
  }

  nts::Tristate QuadNAND::operation(nts::Tristate a, nts::Tristate b) const
  {
    return (static_cast<nts::Tristate>(
        !(static_cast<bool>(a) && static_cast<bool>(b))));
  }
}