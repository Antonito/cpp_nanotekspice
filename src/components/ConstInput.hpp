#ifndef CONSTINPUT_HPP_
#define CONSTINPUT_HPP_

#include "Component.hpp"

namespace nts
{
  class ConstInput : public Component<1>, public IOperable
  {
  public:
    ConstInput(std::string const &type, Tristate res);
    virtual ~ConstInput(){};

    virtual void doOperation();

  private:
    Tristate m_res;
  };
}

#endif // !CONSTINPUT_HPP_