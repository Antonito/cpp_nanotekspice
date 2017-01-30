#ifndef FLIPFLOP_HPP_
#define FLIPFLOP_HPP_

#include <string>
#include "Component.hpp"
#include "IOperable.hpp"
#include "Gates.hpp"

namespace nts
{
  class FlipFlop : public Component<6>, public IOperable
  {
  public:
    FlipFlop(std::string const &type = "Flip-Flop");
    virtual ~FlipFlop();

    virtual void doOperation();
  };
}

#endif // !FLIPFLOP_HPP_