#include "kmint/pigisland/states/hunting.hpp"
#include "kmint/pigisland/states/wander.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  void HuntingState::think()
  {
    if(!hasSmelled){
      context->changeState(std::make_unique<WanderingState>());
    }
    //TODO: calculate closest target and save
  }

  void HuntingState::move()
  {
    std::cout << "hunting move" << std::endl;
    //TODO: gebruik A* om naar een biggeetje te gaan
  }
}
}