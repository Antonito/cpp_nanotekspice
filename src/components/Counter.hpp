#ifndef COUNTER_HPP_
#define COUNTER_HPP_

#include <string>
#include "Component.hpp"

namespace nts
{
  class Counter : public Component<16>, public IOperable
  {
  public:
    Counter(std::string const &type);
    virtual ~Counter();

    virtual void doOperation();

  private:
    uint32_t m_val;
    Pin *    m_output[12];
    Tristate m_lastClk;
  };
}

#endif // !COUNTER_HPP_