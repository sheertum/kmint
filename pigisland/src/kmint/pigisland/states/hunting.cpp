#include "kmint/pigisland/states/hunting.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
namespace pigisland {
  HuntingState::HuntingState(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context, map::map_node* smellTarget, bool isScared) : State(graph, restTarget, energy, context, isScared) {
    _smellTarget = smellTarget;
    createPath(smellTarget);
    calculateNextStep();
    calculateStepCost();
  }

  void HuntingState::sense() {
      State::sense();
      if (&context->node() == *_path.begin())
      {
          context->updateState(updateTransitionState(this));
      }
  }

  void HuntingState::collide() 
  {
    eat();
  }

  void HuntingState::calculateNextStep() 
  {
    _nextStep = *_nextPathStep;
    _nextStep->tagged(false);
    if (_nextPathStep != _path.begin()) {
      _nextPathStep--;
    }
  }
}
}