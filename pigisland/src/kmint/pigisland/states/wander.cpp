#include "kmint/pigisland/states/wander.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {
  WanderingState::WanderingState(map::map_graph& graph) : State(graph){}
  
  WanderingState::WanderingState(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context) : State(graph, restTarget, energy, context){}
  
  void WanderingState::move()
  {
    int next_index = random_int(0, context->node().num_edges());
    context->node(context->node()[next_index].to());
    _energy--;
  }

  void WanderingState::collide() 
  {
    eat();
  }
}
}