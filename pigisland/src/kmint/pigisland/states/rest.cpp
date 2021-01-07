#include "kmint/pigisland/states/rest.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  void RestingState::think()
  {
    context->resetEnergy();
    //TODO: if node is rest switch naar Wandering 
  }
  
  void RestingState::move()
  {
    //TODO: implement A*
  }
}
}