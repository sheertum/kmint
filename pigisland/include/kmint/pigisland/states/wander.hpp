#pragma once

#include "state.hpp"

namespace kmint {
namespace pigisland {
  class WanderingState : public State {
  public:
    WanderingState(map::map_graph& graph);
    WanderingState(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context);
    virtual ~WanderingState() = default;
    void move() override;
    void collide() override;
  };
}
}