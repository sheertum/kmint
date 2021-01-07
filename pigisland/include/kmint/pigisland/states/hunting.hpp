#pragma once

#include "state.hpp"

namespace kmint {
namespace pigisland {
  class HuntingState : public State{
  public:
    HuntingState() = default;
    virtual ~HuntingState() = default;
    void move() override;
    void setContext(shark*) override;
    void collide() override;
  };
}
}