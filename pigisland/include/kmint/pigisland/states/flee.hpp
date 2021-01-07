#pragma once

#include "state.hpp"

namespace kmint {
namespace pigisland {
  class FleeState : public State {
  public:
    FleeState();
    ~FleeState() = default;
    void think() override;
    void move() override;
  private:
    int _wanderingTick;
  };
}
}