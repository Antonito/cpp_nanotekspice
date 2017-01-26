#include "AQuadSimple.hpp"

namespace nts
{
  AQuadSimple::AQuadSimple(std::string const &name) : Component(name)
  {
  }

  nts::Tristate AQuadSimple::Compute(size_t pin)
  {
    nts::Tristate result = nts::UNDEFINED;
    size_t        p;

    // Check if this pin exist
    if (pin < 1 || pin > 12)
      {
	throw std::logic_error("There is no such pin on this chipset");
      }
    // Check if this pin is an output
    if (pin != 3 && pin != 4 && pin != 9 && pin != 10)
      {
	throw std::logic_error("This pin is not an output");
      }

    if (pin < 5)
      p = pin - 3;
    else
      p = pin - 7;
    // If this pin is already computing, return last result
    if (m_compute[p])
      {
	return (m_out[p]);
      }

    // Activate computing for this pin
    m_compute[p] = true;

    // Compute the two inputs
    nts::Tristate a = m_in[2 * p].first->Compute(m_in[2 * p].second);
    nts::Tristate b = m_in[2 * p + 1].first->Compute(m_in[2 * p + 1].second);

    // If both are defined, compute the result
    if (a != nts::UNDEFINED && b != nts::UNDEFINED)
      {
	result = this->operation(a, b);
      }

    // Computing is finished for this pin
    m_compute[p] = false;
    m_out[p] = result;
    return (result);
  }

  void AQuadSimple::SetLink(size_t pin, nts::IComponent &comp, size_t target)
  {
    // Check if this pin exist
    if (pin < 1 || pin > 12)
      {
	throw std::logic_error("There is no such pin on this chipset");
      }
    // Check if this pin is an output
    if (pin == 3 || pin == 4 || pin == 9 || pin == 10)
      {
	throw std::logic_error("This pin is not an input");
      }

    size_t p;

    if (pin < 3)
      p = pin - 1;
    else if (pin < 9)
      p = pin - 3;
    else
      p = pin - 5;

    m_in[p].first = &comp;
    m_in[p].second = target;
  }
}