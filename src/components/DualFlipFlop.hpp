#ifndef DUALFLIPFLOP_HPP_
#define DUALFLIPFLOP_HPP_

#include <string>
#include "Component.hpp"
#include "FlipFlop.hpp"

namespace nts
{
  class DualFlipFlop : public Component<14>
  {
  public:
    DualFlipFlop(std::string const &type);
    virtual ~DualFlipFlop();

  private:
    FlipFlop m_latch[2];
  };
}

#endif // !DUALFLIPFLOP_HPP_