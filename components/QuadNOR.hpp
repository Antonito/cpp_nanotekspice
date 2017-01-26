#ifndef QUADNOR_HPP_
#define QUADNOR_HPP_

#include "AQuadSimple.hpp"

namespace nts
{
  class QuadNOR : public AQuadSimple
  {
  public:
    QuadNOR();
    virtual ~QuadNOR();

  private:
    virtual nts::Tristate operation(nts::Tristate, nts::Tristate) const = 0;
  };
}

#endif // !QUADNOR_HPP_