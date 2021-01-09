#pragma once

#include "state.hpp"

namespace kmint {
namespace pigisland {
  class HuntingState : public State{
  public:
    HuntingState(map::map_graph& graph, map::map_node* restTarget, int energy, shark* context_, map::map_node* smellTarget, bool isScared);
    virtual ~HuntingState() = default;
    void sense() override;
    void collide() override;
    void calculateNextStep() override;
  };
}
}