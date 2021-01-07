#include "kmint/pigisland/states/rest.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  
  void RestingState::sense()
  {
    State::sense();
    //TODO: check of je op de rest zit
    context->resetEnergy();
  }

  void RestingState::think(){
    if(context->getEnergy() == 100){
      context->updateState();
    }
  }

  void RestingState::move()
  {
    //TODO: implement A*
  }
}
}