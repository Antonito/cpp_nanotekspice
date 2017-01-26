#ifndef QUADOR_HPP_
#define QUADOR_HPP_

#include "AQuadSimple.hpp"

namespace nts
{
  class QuadOR : public AQuadSimple
  {
  public:
    QuadOR();
    virtual ~QuadOR();

  private:
    virtual nts::Tristate operation(nts::Tristate, nts::Tristate) const = 0;
  };
}

#endif // !QUADOR_HPP_