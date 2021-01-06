#include "kmint/pigisland/states/wander.hpp"
#include "kmint/pigisland/states/hunting.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
namespace pigisland {
  void WanderingState::think()
  {
    if(hasSmelled){
      context->changeState(std::make_unique<HuntingState>());
    }
    else {
      move();
    }
  }

  void WanderingState::move()
  {
    int next_index = random_int(0, context->node().num_edges());
    context->node(context->node()[next_index].to());
  }
}
}