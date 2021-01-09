#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/probabilistic/boat_wander.hpp"
#include <memory>
namespace kmint {
namespace pigisland {
  boat::boat(map::map_graph& g, map::map_node& initial_node)
    : play::map_bound_actor{ initial_node },
      drawable_{ *this, graphics::image{boat_image()} } {
      changeState(std::make_unique<BoatWanderState>());
      _state->setdocks(g);
      }


  void boat::act(delta_time dt) {
    t_passed_ += dt;
    _state->boardPig();
    _state->sense();
    if (to_seconds(t_passed_) >= _state->getStepWeight()) {
      _state->move();
      t_passed_ = from_seconds(0);
    }
  }

  void boat::changeState(std::unique_ptr<BaseState> newState){
    _state.reset();
    _state = std::move(newState);
    _state->setContext(this);
  }

} // namespace pigisland
} // namespace kmint
