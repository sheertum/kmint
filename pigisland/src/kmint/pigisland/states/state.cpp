#include "kmint/pigisland/states/state.hpp"
#include "kmint/pigisland/states/state_machine.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/random.hpp"


namespace kmint {
namespace pigisland {
  void State::sense()
  {
    float smallestDistance = 700;
    map::map_node* newSmellTarget = nullptr;

    for (auto i = context->begin_perceived(); i != context->end_perceived(); ++i) {
      auto const& a = *i;
      auto xDistance = abs(a.location().x() - context->location().x());
      auto yDistance = abs(a.location().y() - context->location().y());
      auto distance = sqrt(xDistance * xDistance + yDistance * yDistance);
      
      if(typeid(a) == typeid(boat)){
        context->setIsScared(distance <= 50);
        return;
      }

      if(smallestDistance >= distance){
        smallestDistance = distance;
        newSmellTarget = &find_closest_node_to(context->getGraph(), a.location());
      }
    }
    context->setSmellTarget(newSmellTarget);
  }

  void State::think(){
    if(context->needsStateUpdate()){
      context->updateState();
    }
  }

  void State::setContext(shark* context_){
      context = context_;
  }

  void State::wander(){
    int next_index = random_int(0, context->node().num_edges());
    context->node(context->node()[next_index].to());
  }

  void State::moveToTarget(){
    auto node = *_nextStep;
    context->node(*node);
    if (_nextStep != _path.begin()) {
      _nextStep--;
    }
    else {
      context->updateState();
    }
  }

  void State::setPath(Node* target){
    auto& start = find_closest_node_to(context->getGraph(), context->location()) ;
    bool found;
    _path = AStar::getPath(start, *target, found);
    _nextStep = _path.end();
    _nextStep--;
  }

  void State::eat()
  {
    for (auto i = context->begin_collision(); i != context->end_collision(); ++i) {
      auto const& a = *i;
      auto xDistance = abs(a.location().x() - context->location().x());
      auto yDistance = abs(a.location().y() - context->location().y());
      auto distance = sqrt(xDistance * xDistance + yDistance * yDistance);
      i->remove();
    }
  }

  void State::collide(){};
}
}