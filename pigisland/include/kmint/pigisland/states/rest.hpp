#pragma once

#include "state.hpp"

namespace kmint {
namespace pigisland {
  class RestingState : public State {
  public:
    RestingState() = default;
    ~RestingState() = default;
    void think() override;
    void move() override;
  };
}
}