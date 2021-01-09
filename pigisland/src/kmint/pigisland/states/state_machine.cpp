#include "kmint/pigisland/states/state_machine.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  StateMachine::StateMachine(shark* context)
  {
    _context = std::shared_ptr<shark>(context);
  }

  std::unique_ptr<State> StateMachine::updateTransitionState()
  {
    if(_context->getEnergy() <= 0)
    {
      return std::make_unique<RestingState>();
    }

    if(_context->isScared())
    {
      return std::make_unique<FleeState>();
    }
    
    if(_context->hasSmell())
    {
      return std::make_unique<HuntingState>();
    }
    return std::make_unique<WanderingState>();
  }
}
}