#ifndef OUTPUT_HPP_
#define OUTPUT_HPP_

#include "Component.hpp"
#include "IOperable.hpp"

namespace nts
{
  class Output : public Component<1>
  {
  public:
    Output();
    Output(Output const &other) = delete;
    virtual ~Output(){};

    Output &operator=(Output const &other) = delete;
    Tristate getValue();
    Tristate getLastValue() const;
  };
}

#endif // !OUTPUT_HPP_