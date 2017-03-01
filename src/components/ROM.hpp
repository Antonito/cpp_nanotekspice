#ifndef ROM_HPP_
#define ROM_HPP_

#include <string>
#include "Component.hpp"

namespace nts
{
  class ROM : public Component<24>, public IOperable
  {
  public:
    ROM(std::string const &type, std::string const &val);
    virtual ~ROM(){};

    virtual void doOperation();
  };
}

#endif // !ROM_HPP_
