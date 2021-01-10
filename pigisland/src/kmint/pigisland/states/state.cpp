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
#include "kmint/pigisland/Evolution.hpp"

namespace kmint {
namespace pigisland {
  State::State(map::map_graph& graph) : _graph{ graph }, _energy{ 100 }, _smellTarget{ nullptr }, context{ nullptr }, _restTarget{ nullptr }, _isScared{ false }, _stateColor{ 0,0,0 }{
    _restTarget = &find_node_of_kind(graph, 'K');
  }

  State::State(map::map_graph& graph, map::map_node* restTarget, int energy, shark* context_, bool isScared) : _graph{ graph }, _energy{ energy }, _restTarget{ restTarget }, context{ context_ }, _isScared{isScared}, _smellTarget{nullptr}, _stateColor{ 0,0,0 } {}

  void State::setContext(shark* context_){
      context = context_;
  }

  void State::setColor()
  {
      context->getDrawable().set_tint(_stateColor);
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
        _smellTarget = nullptr;
        return;
      }

      if(smallestDistance >= distance){
        smallestDistance = distance;
        newSmellTarget = &find_closest_node_to(_graph, a.location());
      }
    }
    _smellTarget = newSmellTarget;
    calculateStepCost();
  }

  void State::think(){    
    calculateNextStep();
    auto newState = getNewState();
    if(newState != nullptr ){
      context->updateState(std::move(newState));
    }
  }

  void State::move()
  {
    context->node(*_nextStep);
    _energy--;
  }

  void State::createPath(Node* target){
    auto& start = find_closest_node_to(_graph, context->location()) ;
    bool found;
    _path = AStar::getPath(start, *target, found);
    _nextPathStep = _path.end();
    _nextPathStep--;
  }

  void State::calculateStepCost()
  {
    auto type = &context->node().node_info().kind;
    if(*type == 'R')
    {
      _nextStepWeight = 4; 
    } 
    else 
    {
      _nextStepWeight = 1;
    }
  }

  void State::eat()
  {
    for (auto i = context->begin_collision(); i != context->end_collision(); i++) {
        if (typeid((*i)) == typeid(pig))
        {
            Evolution::getInstance().addPig(((pig&)*i).data(), 1);
            i->remove();
        }
        else if (typeid((*i)) == typeid(boat))
        {
        }
    }
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

  int State::getStepWeight()
  {
    return _nextStepWeight;
  }

  std::unique_ptr<State> State::updateTransitionState(State* state)
  {
    if(_energy <= 0)
    {
      return std::make_unique<RestingState>(_graph, _restTarget, _energy, context, _isScared);
    }

    if(_isScared)
    {
      return std::make_unique<FleeState>(_graph, _restTarget, _energy, context, _isScared);
    }
    
    if(_smellTarget)
    {
      return std::make_unique<HuntingState>(_graph, _restTarget, _energy, context, _smellTarget, _isScared);
    }

    return std::make_unique<WanderingState>(_graph, _restTarget, _energy, context, _isScared);
  }

  void State::collide(){};
}
}