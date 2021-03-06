#ifndef PIN_HPP_
#define PIN_HPP_

#include <vector>
#include <utility>
#include <ostream>
#include "IOperable.hpp"

namespace nts
{
  class AGate;

  class Pin
  {
  public:
    enum Mode
    {
      DEAD = -1,
      INPUT,
      HYBRID,
      OUTPUT
    };

    explicit Pin(Mode mode, IOperable *gate = nullptr);
    Pin(Pin const &other) = delete;
    ~Pin();

    Pin &operator=(Pin const &other) = delete;

    Mode getMode() const;
    Pin *setMode(Mode mode, IOperable *gate = nullptr);
    nts::Tristate getValue();
    nts::Tristate getLastValue() const;
    void setValue(Tristate value);
    nts::Tristate compute();
    void          setLink(IComponent &, size_t);

  private:
    std::pair<IComponent *, size_t> m_link;
    Mode          m_mode;
    IOperable *   m_gate;
    nts::Tristate m_lastValue;
    bool          m_computing;
    size_t        m_simId;
  };
}

std::ostream &operator<<(std::ostream &os, nts::Pin const &p);

#endif // !PIN_HPP_