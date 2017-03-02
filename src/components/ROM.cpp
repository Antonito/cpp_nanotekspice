#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include "ROM.hpp"
#include "InvalidInput.hpp"

namespace nts
{
  ROM::ROM(std::string const &type, std::string const &value) : Component(type)
  {
    std::ifstream file(value, std::ios::binary);
    int           addrIn[] = {7, 6, 5, 4, 3, 2, 1, 0, 22, 21, 18};
    int           dataOut[] = {8, 9, 10, 12, 13, 14, 15, 16};
    struct stat   statBuf;
    int           rc;

    if (!file.is_open())
      {
	throw InvalidInput("Cannot open ROM file: " + value);
      }
    rc = stat(value.c_str(), &statBuf);
    if (rc == 0 || statBuf.st_size < static_cast<signed>(sizeof(m_file)))
      {
	throw InvalidInput("File is to small: " + value);
      }
    file.read(m_file, statBuf.st_size);
    file.close();
    for (size_t i = 0; i < 11; ++i)
      {
	m_addrInput[i] = m_pins[addrIn[i]];
	m_addrInput[i]->setMode(Pin::INPUT);
      }
    for (size_t i = 0; i < 8; ++i)
      {
	m_data[i] = m_pins[dataOut[i]];
	m_data[i]->setMode(Pin::OUTPUT, this);
	m_data[i]->setValue(Tristate::FALSE);
      }
    m_outEnable = m_pins[19];
    m_outEnable->setMode(Pin::INPUT);
    m_chipEnable = m_pins[17];
    m_chipEnable->setMode(Pin::INPUT);
  }

  void ROM::doOperation()
  {
    int  x;
    int  y;
    char requ_byte;

    if (m_chipEnable->getValue())
      {
	x = m_addrInput[0]->getValue() | (m_addrInput[1]->getValue() << 1) |
	    (m_addrInput[2]->getValue() << 2) |
	    (m_addrInput[3]->getValue() << 3);
	y = m_addrInput[4]->getValue() | (m_addrInput[5]->getValue() << 1) |
	    (m_addrInput[6]->getValue() << 2) |
	    (m_addrInput[7]->getValue() << 3) |
	    (m_addrInput[8]->getValue() << 4) |
	    (m_addrInput[9]->getValue() << 5) |
	    (m_addrInput[10]->getValue() << 6);
	if (m_outEnable->getValue())
	  {
	    requ_byte = m_file[y * x];
	    for (size_t i = 0; i < 8; ++i)
	      {
		m_data[i]->setValue(((requ_byte & (1 << i)) != 0)
		                        ? nts::Tristate::TRUE
		                        : nts::Tristate::FALSE);
	      }
	  }
      }
  }
}