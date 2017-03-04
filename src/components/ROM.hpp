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

  private:
    Pin *m_addrInput[11];
    Pin *m_data[8];
    Pin *m_outEnable;
    Pin *m_chipEnable;
    char m_file[16384 / 8];
  };
}

#endif // !ROM_HPP_
