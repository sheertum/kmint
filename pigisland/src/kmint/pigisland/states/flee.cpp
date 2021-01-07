#include "kmint/pigisland/states/flee.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  FleeState::FleeState() : State(), _wanderingTick{10}{}
  void FleeState::think()
  {
    //TODO: if node is rest switch naar Wandering 
  }
  
  void FleeState::move()
  {
    wander();
    _wanderingTick--;
  }
}
}