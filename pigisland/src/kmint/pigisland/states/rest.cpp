#include "kmint/pigisland/states/rest.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  RestingState::RestingState(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context, bool isScared) : State(graph, restTarget, energy, context, isScared){
    createPath(_restTarget);
    calculateNextStep();
    calculateStepCost();
  }

  void RestingState::sense()
  {
    State::sense();
    if(context->location() == _restTarget->location()){
      resetEnergy();
    }
  }

  void RestingState::think(){
    calculateNextStep();
    if(_energy == 100){
      context->updateState(updateTransitionState(this));
    }
  }

  void RestingState::calculateNextStep() 
  {
    _nextStep = *_nextPathStep;
    _nextStep->tagged(false);
    if (_nextPathStep != _path.begin()) {
      _nextPathStep--;
    }
  }
}
}
