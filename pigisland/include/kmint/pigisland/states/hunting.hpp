#pragma once

#include "state.hpp"

namespace kmint {
namespace pigisland {
  class HuntingState : public State{
  public:
    HuntingState() = default;
    virtual ~HuntingState() = default;
    void think() override;
    void move() override;
  };
}
}