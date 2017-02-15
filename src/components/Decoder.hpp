#ifndef DECODER_HPP_
#define DECODER_HPP_

#include <string>
#include "Component.hpp"

namespace nts
{
  class Decoder : public Component<24>, public IOperable
  {
  public:
    Decoder(std::string const &type);
    virtual ~Decoder(){};

    virtual void doOperation();

  private:
    Pin *m_input[4];
    Pin *m_output[16];
    Pin *m_strobe;
    Pin *m_inhibit;
  };
}

#endif // !DECODER_HPP_