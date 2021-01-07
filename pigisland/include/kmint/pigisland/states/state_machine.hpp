#pragma once

#include "state.hpp"
#include "flee.hpp"
#include "rest.hpp"
#include "wander.hpp"
#include "hunting.hpp"

namespace kmint {
namespace pigisland {
  class shark;

  class StateMachine{
  public:
    StateMachine(shark*);
    std::unique_ptr<State> updateTransitionState();
  private:
    std::shared_ptr<shark> _context;
  };
}
}