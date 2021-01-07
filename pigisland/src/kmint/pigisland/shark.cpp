#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/states/wander.hpp"

#include <iostream>

namespace kmint {
namespace pigisland {
shark::shark(map::map_graph &g, map::map_node &initial_node) : play::map_bound_actor{initial_node}, drawable_{*this, graphics::image{shark_image()}}, _energy{100}, _hasSmell{false} {
  changeState(std::make_unique<WanderingState>());
}

void shark::act(delta_time dt) {
  t_passed_ += dt;
  if (to_seconds(t_passed_) >= 0.1) {
    _state->act();
     t_passed_ = from_seconds(0);
  }
}

void shark::changeState(std::unique_ptr<State> nextState){
  _state = std::move(nextState);
  _state->setContext(this);
}

void shark::setHasSmell(bool hasSmell_)
{
  _hasSmell = hasSmell_;
}

bool shark::hasSmell()
{
  return _hasSmell;
}

void shark::setIsScared(bool isScared)
{
  _isScared = isScared;
}

bool shark::isScared()
{
  return isScared;
}

void shark::decreaseEnergy()
{
  if(_energy > 0){
    _energy--;
  }
}

int shark::getEnergy()
{
  return _energy;
}

void shark::resetEnergy()
{
  _energy=100; 
}

} // namespace pigisland
} // namespace kmint
