#include "kmint/pigisland/states/wander.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  void WanderingState::think()
  {
    if(context->hasSmell()){
      // context->changeState(std::make_unique<HuntingState>());
    }
    else {
      move();
    }
  }

  void WanderingState::move()
  {
    wander();
  }
}
}