#include "kmint/pigisland/states/wander.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  void WanderingState::move()
  {
    wander();
  }

  void WanderingState::collide() 
  {
    eat();
  }
}
}