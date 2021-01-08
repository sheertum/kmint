#pragma once
#include "kmint/pigisland/AStar.h"
#include <map>
namespace kmint {
namespace pigisland {
  class boat;

  class BaseState {
  public:
    BaseState(int paintJob, std::map<Node*, float> chances, std::map<map::map_node*, std::tuple<int, int>> docks);
    ~BaseState() = default;
    virtual void move() = 0;
    virtual void sense() = 0;
    void increasePaintDamage();
    void repairPaintjob(int amount);
    void setContext(boat*);
    void boardPig();
    void setdocks(map::map_graph& g);
  protected:
    boat* _context;
    int _paintDamage;
    const int _paintDamageThreshold = 2;
    std::map<map::map_node*, float> _chances;
    std::map<map::map_node*, std::tuple<int, int>> _docks;
  };
}
}