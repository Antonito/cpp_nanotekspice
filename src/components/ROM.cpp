#include "ROM.hpp"

#pragma message("ROM a implementer")

namespace nts
{
  ROM::ROM(std::string const &type, std::string const &value) : Component(type)
  {
    (void)value;
  }

  void ROM::doOperation()
  {
  }
}