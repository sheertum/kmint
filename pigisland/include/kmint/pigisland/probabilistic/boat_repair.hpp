#include "boat_basestate.hpp"
namespace kmint {
namespace pigisland {
  class boat;

  class BoatRepairState : public BaseState{
    public:
      BoatRepairState(int paintJob, std::map<Node*, float> chances, std::map<map::map_node*, std::tuple<int, int>> docks);
      void move() override;
      void sense() override;
      void moveToDock();
      map::map_node* pickDock();
      void setPath();
      void repair();
      void updateDock(int repairAmount);
    private:
      map::map_node* _pickedDock;
      std::list<kmint::map::map_node*> _path;
      std::list<kmint::map::map_node *>::iterator _nextStep;
  };
}
}