#include "..\..\..\..\include\kmint\pigisland\states\state.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  void State::act(){
    sense();
    think();
  }

  void State::sense()
  {
    checkSleep();
    for (auto i = context->begin_perceived(); i != context->end_perceived(); ++i) {
      auto const& a = *i;
      auto distance = sqrt(a.location().x() * a.location().x() + a.location().y() * a.location().y());
      std::cout << distance << std::endl;

      if (distance > 200) {
        hasSmelled = true;
      }
    }
  }

  void State::checkSleep(){
    context->energy--;
    if(context->energy <= 0){
      //TODO switch to rest
        return;
    }
  }

  void State::setContext(shark* context_){
      context = context_;
  }
}
}