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
    size_t   m_count;
    FlipFlop m_latch[4];
    Pin *    m_output[16];
    Tristate m_lastClk;
  };
}

#endif // !DECODER_HPP_