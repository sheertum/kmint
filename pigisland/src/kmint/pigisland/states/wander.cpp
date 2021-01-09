#include "kmint/pigisland/states/wander.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {
  WanderingState::WanderingState(map::map_graph& graph) : State(graph){}
  
  WanderingState::WanderingState(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context, bool isScared) : State(graph, restTarget, energy, context, isScared){
    calculateNextStep();
    calculateStepCost();
  }

  void WanderingState::collide() 
  {
    eat();
  }

  void WanderingState::calculateNextStep() 
  {
    int next_index = random_int(0, context->node().num_edges());
    _nextStep = &context->node()[next_index].to();
  }
}
}