#ifndef NODEGATE_HPP_
#define NODEGATE_HPP_

#include "Component.hpp"
#include "IOperable.hpp"

namespace nts
{
  class NodeGate : public Component<2>, public IOperable
  {
  public:
    NodeGate();
    virtual ~NodeGate();

    virtual void doOperation();
  };
}

#endif // !NORGATE_HPP_