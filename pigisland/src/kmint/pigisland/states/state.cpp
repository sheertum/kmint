#include "..\..\..\..\include\kmint\pigisland\states\state.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  State::State(std::shared_ptr<shark> actor) : context{ actor } {}

  void State::act(){
    checkSleep();
    sense();
    think();
    move();
  }

  void State::checkSleep(){
    context->energy--;
    if(context->energy <= 0){
      //TODO switch to rest
    }
    std::cout << context->energy << std::endl;
  }
}
}