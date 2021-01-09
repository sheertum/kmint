#include "boat_basestate.hpp"
namespace kmint {
namespace pigisland {
  class boat;

  class BoatWanderState : public BaseState {
  public:
      BoatWanderState(int paintJob, std::map<Node*, float> chances, std::map<map::map_node*, std::tuple<int, int>> docks);
      explicit BoatWanderState();
      void move() override;
      void sense() override;
  };
}
}