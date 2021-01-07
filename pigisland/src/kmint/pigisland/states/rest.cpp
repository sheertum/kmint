#include "kmint/pigisland/states/rest.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  void RestingState::setContext(shark* context_)
  {
    State::setContext(context_);
    setPath(context->getRestTarget());
  }


  void RestingState::sense()
  {
    State::sense();
    if(context->location() == context->getRestTarget()->location()){
      context->resetEnergy();
      context->updateState();
    }
  }

  void RestingState::think(){
    if(context->getEnergy() == 100){
      context->updateState();
    }
  }

  void RestingState::move()
  {
    moveToTarget();
  }
}
}