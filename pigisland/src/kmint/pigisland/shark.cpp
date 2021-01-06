#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/states/wander.hpp"

#include <iostream>

namespace kmint {
namespace pigisland {
shark::shark(map::map_graph &g, map::map_node &initial_node) : play::map_bound_actor{initial_node}, drawable_{*this, graphics::image{shark_image()}} {
  changeState(std::make_unique<WanderingState>());
}

void shark::act(delta_time dt) {
  t_passed_ += dt;
  if (to_seconds(t_passed_) >= 0.1) {
    state->act();
     t_passed_ = from_seconds(0);
  }
}

void shark::changeState(std::unique_ptr<State> nextState){
  state = std::move(nextState);
  state->setContext(this);
  state->act();
}
} // namespace pigisland
} // namespace kmint
