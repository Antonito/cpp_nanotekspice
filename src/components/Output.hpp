#ifndef OUTPUT_HPP_
#define OUTPUT_HPP_

#include "Component.hpp"
#include "IOperable.hpp"

namespace nts
{
  class Output : public Component<1>, public IOperable
  {
  public:
    Output();
    Output(Output const &other) = delete;
    ~Output();

    Output &operator=(Output const &other) = delete;
    virtual nts::Tristate doOperation();
  };
}

#endif // !OUTPUT_HPP_