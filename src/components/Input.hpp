#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <string>
#include "Component.hpp"
#include "IOperable.hpp"

namespace nts
{
  class Input : public Component<1>, public IOperable
  {
  public:
    enum InputType
    {
      INPUT,
      CLOCK
    };

    Input(InputType type, std::string const &value);
    Input(Input const &other) = delete;
    virtual ~Input(){};

    Input &operator=(Input const &other) = delete;

    void         setValue(Tristate);
    void         changeValue(Tristate);
    void         update();
    virtual void doOperation();

  private:
    InputType m_type;
    Tristate  m_value;
  };
}

#endif // !INPUT_HPP_