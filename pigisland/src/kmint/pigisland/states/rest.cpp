#include "kmint/pigisland/states/rest.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  RestingState::RestingState(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context) : State(graph, restTarget, energy, context){
    createPath(_restTarget);
  }

  void RestingState::sense()
  {
    State::sense();
    if(context->location() == _restTarget->location()){
      resetEnergy();
    }
  }

  void RestingState::think(){
    if(_energy == 100){
      context->updateState(updateTransitionState(this));
    }
  }

  void RestingState::move()
  {
    setNextStepOnPath();
  }
}
}
