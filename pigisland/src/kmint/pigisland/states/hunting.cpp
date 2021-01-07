#include "kmint/pigisland/states/hunting.hpp"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
namespace pigisland {
  void HuntingState::setContext(shark* context_)
  {
    State::setContext(context_);
    setPath(context->getSmellTarget());
  }

  void HuntingState::move()
  {
    std::cout << "hunting move" << std::endl;
    moveToTarget();
  }
}
}