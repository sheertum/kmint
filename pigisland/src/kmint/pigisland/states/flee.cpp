#include "kmint/pigisland/states/flee.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  FleeState::FleeState() : State(), _wanderingTick{10}{}
  void FleeState::think()
  {
    if(_wanderingTick <=0 || context->getEnergy() <= 0){
      context->updateState();
    }
  }
  
  void FleeState::move()
  {
    wander();
    _wanderingTick--;
  }
}
}