#include "kmint/pigisland/states/state.hpp"
#include "kmint/pigisland/states/state_machine.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {
  void State::act(){
    sense();
    think();
    context->decreaseEnergy();
  }

  void State::sense()
  {
    checkSleep();
    for (auto i = context->begin_perceived(); i != context->end_perceived(); ++i) {
      auto const& a = *i;
      auto xDistance = abs(a.location().x() - context->location().x());
      auto yDistance = abs(a.location().y() - context->location().y());
      auto distance = sqrt(xDistance * xDistance + yDistance * yDistance);

      if (distance <= 100) {
        hasSmelled = true;
      }
    }
  }

  void State::checkSleep(){
    if(context->getEnergy() <= 0){
      //TODO switch to rest
        return;
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