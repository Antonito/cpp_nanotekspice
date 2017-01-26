#ifndef AQUADSIMPLE_HPP_
#define AQUADSIMPLE_HPP_

#include "IComponent.hpp"

namespace nts
{
  class AQuadSimple : public Component<8, 4>
  {
  public:
    virtual ~AQuadSimple(){};

    virtual nts::Tristate Compute(size_t pin_num_this = 1);
    virtual void SetLink(size_t pin_num_this, nts::IComponent &component,
                         size_t pin_num_target);

  private:
    virtual nts::Tristate operation(nts::Tristate, nts::Tristate) const = 0;
  };
}

#endif // !AQUADSIMPLE_HPP_