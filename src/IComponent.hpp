// Kind of Advanced Language Assistant Laboratory 2006-2042
// Epitech 1999-2042
// Jason Brillante brilla_a brilla_b
//
// NanoTekSpice

#ifndef __ICOMPONENT_HPP__
#define __ICOMPONENT_HPP__

#include <cstdlib>

namespace nts
{
  enum Tristate
  {
    UNDEFINED = (-true),
    TRUE = true,
    FALSE = false
  };

  class IComponent
  {
  public:
    /// Compute value of the precised pin
    virtual nts::Tristate Compute(size_t pin_num_this = 1) = 0;

    /// Useful to link IComponent together
    virtual void SetLink(size_t pin_num_this, nts::IComponent &component,
                         size_t pin_num_target) = 0;

    ///// Print on terminal the name of the component and
    //// the state of every pin of the current component
    /// The output won’t be tested, but it may help you
    // as a trace.
    virtual void Dump(void) const = 0;

    virtual ~IComponent(void)
    {
    }
  };
}

#endif // __ICOMPONENT_HPP__