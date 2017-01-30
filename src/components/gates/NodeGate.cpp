#include "NodeGate.hpp"

namespace nts
{
  NodeGate::NodeGate() : Component("Node")
  {
    m_pins[0] = new Pin(Pin::INPUT);
    m_pins[1] = new Pin(Pin::OUTPUT, this);
  }

  NodeGate::~NodeGate()
  {
    delete m_pins[0];
    delete m_pins[1];
  }

  void NodeGate::doOperation()
  {
    m_pins[1]->setValue(m_pins[0]->getValue());
  }
}