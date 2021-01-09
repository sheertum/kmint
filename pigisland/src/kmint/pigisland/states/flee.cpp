#include "kmint/pigisland/states/flee.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {
  FleeState::FleeState(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context) : State(graph, restTarget, energy, context), _wanderingTick{10}{}

  void FleeState::think()
  {
    if(_wanderingTick <=0 || _energy <= 0){
      context->updateState(updateTransitionState(this));
    }
  }
  
  void FleeState::move()
  {
    int next_index = random_int(0, context->node().num_edges());
    context->node(context->node()[next_index].to());
    _wanderingTick--;
    _energy--;
  }
}
}