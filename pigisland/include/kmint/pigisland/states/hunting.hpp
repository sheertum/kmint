#pragma once

#include "state.hpp"

namespace kmint {
namespace pigisland {
  class HuntingState : public State{
  public:
    HuntingState(map::map_graph& graph, map::map_node* restTarget, int energy, shark* context_, map::map_node* smellTarget);
    virtual ~HuntingState() = default;
    void move() override;
    void collide() override;
  };
}
}