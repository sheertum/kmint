#include "kmint/pigisland/states/flee.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {
  FleeState::FleeState(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context,  bool isScared) : State(graph, restTarget, energy, context, isScared), _wanderingTick{10}{
    calculateNextStep();
    calculateStepCost();
    _stateColor = graphics::color(0,255,0);
  }

  void FleeState::think()
  {
    if(_wanderingTick <=0 || _energy <= 0){
      context->updateState(updateTransitionState(this));
    }
  }
  
  void FleeState::move()
  {
    context->node(*_nextStep);
    _wanderingTick--;
    _energy--;
  }

  void FleeState::calculateNextStep() 
  {
    int next_index = random_int(0, context->node().num_edges());
    _nextStep = &context->node()[next_index].to();
  }

}
}