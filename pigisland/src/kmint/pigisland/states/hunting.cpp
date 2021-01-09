#include "kmint/pigisland/states/hunting.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
namespace pigisland {
  HuntingState::HuntingState(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context, map::map_node* smellTarget) : State(graph, restTarget, energy, context) {
    _smellTarget = smellTarget;
    createPath(smellTarget);
  }

  void HuntingState::move()
  {
    setNextStepOnPath();
    _energy--;
    if (_nextStep == _path.begin()) {
      context->updateState(updateTransitionState(this));
    }
  }

  void HuntingState::collide() 
  {
    eat();
  }
}
}