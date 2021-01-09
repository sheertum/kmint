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
      //std::cout << "resting" << std::endl;
      return std::make_unique<RestingState>();
    }

    if(_context->isScared())
    {
      //std::cout << "fleeing" << std::endl;
      return std::make_unique<FleeState>();
    }
    
    if(_context->hasSmell())
    {
      //std::cout << "hunting" << std::endl;
      return std::make_unique<HuntingState>();
    }
    //std::cout << "wandering" << std::endl;
    return std::make_unique<WanderingState>();
  }
}
}