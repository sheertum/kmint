#pragma once

#include "state.hpp"

namespace kmint {
namespace pigisland {
  class WanderingState : public State {
  public:
    WanderingState() = default;
    virtual ~WanderingState() = default;
    void think() override;
    void move() override;
  };
}
}