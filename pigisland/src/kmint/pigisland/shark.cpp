#include "kmint/random.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/states/state_machine.hpp"

#include <iostream>

namespace kmint {
namespace pigisland {
shark::shark(map::map_graph& g, map::map_node& initial_node) : play::map_bound_actor{ initial_node }, drawable_{ *this, graphics::image{shark_image()} }, _stateMachine{ std::make_unique<StateMachine>(this) }, _energy{ 100 }, _isScared{ false }, _graph{g} {
  updateState();
}

void shark::act(delta_time dt) {
  t_passed_ += dt;
  if (to_seconds(t_passed_) >= 0.1) {
    _state->act();
     t_passed_ = from_seconds(0);
  }
}

bool shark::needsStateUpdate()
{
    auto newstate = _stateMachine->updateTransitionState();
  if(typeid(newstate) == typeid(_state)){
    return false;
  } else {
    return true;
  }
}

void shark::updateState(){
  _state = std::move(_stateMachine->updateTransitionState());
  _state->setContext(this);
}

void shark::setSmellTarget(map::map_node* smellTarget)
{
  _smellTarget = smellTarget;
}

bool shark::hasSmell()
{
  return _smellTarget != nullptr;
}

map::map_node* shark::getSmellTarget()
{
  return _smellTarget;
}

void shark::setIsScared(bool isScared)
{
  _isScared = isScared;
}

bool shark::isScared()
{
  return _isScared;
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

std::unique_ptr<State>& shark::gestState()
{
  return _state;
}

map::map_graph& shark::getGraph()
{
  return _graph;
}

} // namespace pigisland
} // namespace kmint
