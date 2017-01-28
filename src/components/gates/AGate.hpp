#ifndef AGATE_HPP_
#define AGATE_HPP_

#include <string>
#include "Component.hpp"

namespace nts
{
  class AGate : public Component<3>
  {
  public:
    AGate(std::string const &type);
    virtual ~AGate();
    virtual nts::Tristate doOperation() = 0;
  };
}

#endif // !AGATE_HPP_