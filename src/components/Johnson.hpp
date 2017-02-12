#ifndef JOHNSON_HPP_
#define JOHNSON_HPP_

#include <string>
#include "Component.hpp"

namespace nts
{
  class Johnson : public Component<15>, public IOperable
  {
  public:
    Johnson(std::string const &type);
    virtual ~Johnson(){};

    virtual void doOperation();

  private:
    size_t   m_count;
    Pin *    m_output[10];
    Tristate m_lastClk;
  };
}

#endif // !JOHNSON_HPP_