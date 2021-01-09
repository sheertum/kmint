#pragma once

#include "state.hpp"

namespace kmint {
namespace pigisland {
  class WanderingState : public State {
  public:
    WanderingState(map::map_graph& graph);
    WanderingState(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context, bool isScared);
    virtual ~WanderingState() = default;
    void collide() override;
    void calculateNextStep() override;
  };
}
}