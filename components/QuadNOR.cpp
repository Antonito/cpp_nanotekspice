#include "QuadNOR.hpp"

namespace nts
{
  QuadNOR::QuadNOR() : AQuadSimple("4001 (4 NOR)")
  {
  }

  QuadNOR::~QuadNOR()
  {
  }

  nts::Tristate QuadNOR::operation(nts::Tristate a, nts::Tristate b) const
  {
    return (static_cast<nts::Tristate>(
        !(static_cast<bool>(a) || static_cast<bool>(b))));
  }
}