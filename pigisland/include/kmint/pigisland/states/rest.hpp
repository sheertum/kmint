#pragma once

#include "state.hpp"

namespace kmint {
namespace pigisland {
  class RestingState : public State {
  public:
    RestingState(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context);
    ~RestingState() = default;
    void sense() override;
    void think() override;
    void move() override;
  };
}
}