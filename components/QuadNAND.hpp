#ifndef QUADNAND_HPP_
#define QUADNAND_HPP_

#include "AQuadSimple.hpp"

namespace nts
{
  class QuadNAND : public AQuadSimple
  {
  public:
    QuadNAND();
    virtual ~QuadNAND();

  private:
    virtual nts::Tristate operation(nts::Tristate, nts::Tristate) const = 0;
  };
}

#endif // !QUADNAND_HPP_