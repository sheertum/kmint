#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/states/wanderState.hpp"

#include <iostream>

namespace kmint {
namespace pigisland {
shark::shark(map::map_graph &g, map::map_node &initial_node) : play::map_bound_actor{initial_node}, drawable_{*this, graphics::image{shark_image()}} {
  state = std::make_unique<WanderingState>(std::shared_ptr<shark>(this));
}

void shark::act(delta_time dt) {
  t_passed_ += dt;
  if (to_seconds(t_passed_) >= 1) {
    state->act();
     t_passed_ = from_seconds(0);
  }
}

void shark::changeState(std::unique_ptr<State> nextState){
  state = std::move(nextState);
}
} // namespace pigisland
} // namespace kmint
