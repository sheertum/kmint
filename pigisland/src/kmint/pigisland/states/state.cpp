#include "kmint/pigisland/states/state.hpp"
#include "kmint/pigisland/states/state_machine.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {
  void State::act(){
    sense();
    think();
    move();
    context->decreaseEnergy();
  }

  void State::sense()
  {
    for (auto i = context->begin_perceived(); i != context->end_perceived(); ++i) {
      auto const& a = *i;
      auto xDistance = abs(a.location().x() - context->location().x());
      auto yDistance = abs(a.location().y() - context->location().y());
      auto distance = sqrt(xDistance * xDistance + yDistance * yDistance);

      context->setHasSmell(distance <= 100);
      if(typeid(a) == typeid(boat)){
        context->setIsScared(distance <= 50);
      }
    }
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
}
}