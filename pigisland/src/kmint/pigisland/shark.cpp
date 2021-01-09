#include "kmint/random.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/states/wander.hpp"

#include <iostream>

namespace kmint {
namespace pigisland {
shark::shark(map::map_graph& g, map::map_node& initial_node) : play::map_bound_actor{ initial_node }, drawable_{ *this, graphics::image{shark_image()} } {
  updateState(std::make_unique<WanderingState>(g));
  _state->setContext(this);
}

void shark::act(delta_time dt) {
  t_passed_ += dt;
  _state->collide();
  if (to_seconds(t_passed_) >= _state->getStepWeight()) {
    _state->sense();
    _state->think();
    _state->move();
    t_passed_ = from_seconds(0);
  }
}

void shark::updateState(std::unique_ptr<State> newState){
    std::cout << typeid(*newState).name() << std::endl;
  _state = std::move(newState);
}

} // namespace pigisland
} // namespace kmint
