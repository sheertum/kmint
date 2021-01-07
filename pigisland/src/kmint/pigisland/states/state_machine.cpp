#include "kmint/pigisland/states/state_machine.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  StateMachine::StateMachine(shark* context)
  {
    _context = std::shared_ptr<shark>(context);
  }

  void StateMachine::transitionState()
  {
    if(_context->getEnergy() <= 0)
    {
      _context->changeState(std::make_unique<RestingState>());
      return;
    }

    if(_context->isScared())
    {
      _context->changeState(std::make_unique<FleeState>());
      return;
    }

    if(_context->hasSmell())
    {
      _context->changeState(std::make_unique<HuntingState>());
      return;
    }

    _context->changeState(std::make_unique<WanderingState>());
  }
}
}