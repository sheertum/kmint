#pragma once

#include "state.hpp"

namespace kmint {
namespace pigisland {
  class FleeState : public State {
  public:
    FleeState(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context,  bool isScared);
    ~FleeState() = default;
    void think() override;
    void move() override;
    void calculateNextStep() override;
  private:
    void wander();
    int _wanderingTick;
  };
}
}