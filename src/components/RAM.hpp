#ifndef RAM_HPP_
#define RAM_HPP_

#include <string>
#include "Component.hpp"

namespace nts
{
  class RAM : public Component<24>, public IOperable
  {
  public:
    RAM(std::string const &type);
    virtual ~RAM(){};

    virtual void doOperation();

  private:
    Pin *m_addrInput[10];
    Pin *m_dataIO[8];
    Pin *m_writeEnable;
    Pin *m_outputEnable;
    Pin *m_noConnect;
    Pin *m_chipEnable;
    char m_buff[8192 / 8];
  };
}

#endif // !RAM_HPP_
