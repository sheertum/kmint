#include "kmint/pigisland/states/state.hpp"
#include "kmint/pigisland/states/flee.hpp"
#include "kmint/pigisland/states/rest.hpp"
#include "kmint/pigisland/states/wander.hpp"
#include "kmint/pigisland/states/hunting.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/map/map.hpp"
#include "kmint/random.hpp"


namespace kmint {
namespace pigisland {
    State::State(map::map_graph& graph) : _graph{ graph }, _energy{ 100 }, _smellTarget{ nullptr }, context{ nullptr }, _restTarget{ nullptr }{
    _restTarget = &find_node_of_kind(graph, 'K');
  }

  State::State(map::map_graph& graph, map::map_node* restTarget, int energy, shark* context_) : _graph{ graph }, _energy{ energy }, _restTarget{ restTarget }, context{ context_ }, _smellTarget{nullptr} {}

  void State::setContext(shark* context_){
      context = context_;
  }

  void State::sense()
  {
    float smallestDistance = 100;
    _isScared = false;
    map::map_node* newSmellTarget = nullptr;

    for (auto i = context->begin_perceived(); i != context->end_perceived(); ++i) {
      auto const& a = *i;
      auto xDistance = abs(a.location().x() - context->location().x());
      auto yDistance = abs(a.location().y() - context->location().y());
      auto distance = sqrt(xDistance * xDistance + yDistance * yDistance);
      
      if(typeid(a) == typeid(boat)){
        _isScared = (distance <= 50);
        return;
      }

      if(smallestDistance >= distance){
        smallestDistance = distance;
        _smellTarget = &find_closest_node_to(_graph, a.location());
      }
    }
  }

  void State::think(){
    auto newState = getNewState();
    if(newState != nullptr ){
      context->updateState(std::move(newState));
    }
  }

  void State::setNextStepOnPath(){
    auto node = *_nextStep;
    node->tagged(false);
    context->node(*node);
    if (_nextStep != _path.begin()) {
      _nextStep--;
    }
    else {
      //TODO: reset visited nodes that weren't part of the path
      context->updateState(updateTransitionState(this));
    }
  }

  void State::createPath(Node* target){
    auto& start = find_closest_node_to(_graph, context->location()) ;
    bool found;
    _path = AStar::getPath(start, *target, found);
    _nextStep = _path.end();
    _nextStep--;
  }

  void State::eat()
  {
    for (auto i = context->begin_collision(); i != context->end_collision(); ++i) {
      i->remove();
    }
  }

  map::map_node* State::getSmellTarget()
  {
    return _smellTarget;
  }

  bool State::isScared()
  {
    return _isScared;
  }

  int State::getEnergy(){
    return _energy;
  }

  map::map_graph& State::getGraph(){
    return _graph;
  }
  
  void State::resetEnergy()
  {
    _energy=100; 
  }

  std::unique_ptr<State> State::getNewState()
  {
    auto newstate = updateTransitionState(this);
      if(typeid(*newstate) == typeid(*this)){
      return nullptr;
    } 
    else {
      return newstate;
    }
  }

  std::unique_ptr<State> State::updateTransitionState(State* state)
  {
    map::map_node* restTarget = getRestTarget();
    std::cout << _energy << std::endl;
    if(_energy <= 0)
    {
      return std::make_unique<RestingState>(_graph, _restTarget, _energy, context);
      std::cout << "RestingState" << std::endl;
    }

    if(_isScared)
    {
      return std::make_unique<FleeState>(_graph, _restTarget, _energy, context);
      std::cout << "FleeState" << std::endl;
    }
    
    if(_smellTarget)
    {
      return std::make_unique<HuntingState>(_graph, _restTarget, _energy, context, _smellTarget);
      std::cout << "HuntingState" << std::endl;
    }

    return std::make_unique<WanderingState>(_graph, _restTarget, _energy, context);
    std::cout << "WanderingState" << std::endl;
  }

  void State::collide(){};
}
}