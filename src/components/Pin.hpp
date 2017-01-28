#ifndef PIN_HPP_
#define PIN_HPP_

#include <vector>
#include <utility>
#include <ostream>

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

    explicit Pin(Mode mode, AGate *gate = nullptr);
    Pin(Pin const &other);
    ~Pin();

    Pin &operator=(Pin const &other);

    Mode          getMode() const;
    nts::Tristate getValue();
    nts::Tristate getLastValue() const;
    nts::Tristate compute();
    void          setLink(IComponent &, size_t);

  private:
    std::pair<IComponent *, size_t> m_link;
    Mode          m_mode;
    AGate *       m_gate;
    nts::Tristate m_lastValue;
    bool          m_computing;
  };
}

std::ostream &operator<<(std::ostream &os, nts::Pin const &p);

#endif // !PIN_HPP_