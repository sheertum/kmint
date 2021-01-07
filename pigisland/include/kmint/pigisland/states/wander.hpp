#pragma once

#include "state.hpp"

namespace kmint {
namespace pigisland {
  class WanderingState : public State {
  public:
    WanderingState() = default;
    virtual ~WanderingState() = default;
    void move() override;
    void collide() override;
  };
}
}