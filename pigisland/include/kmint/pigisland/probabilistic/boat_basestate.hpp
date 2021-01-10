#pragma once
#include "kmint/pigisland/AStar.h"
#include "kmint/graphics/color.hpp"
#include "kmint/pigisland/pig.hpp"
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
    void calculateStepCost();
    int getStepWeight();
    void setColor();
  protected:
    std::vector<pig> _collectedPigs;
    graphics::color _stateColor;
    boat* _context;
    int _nextStepWeight;
    int _paintDamage;
    const int _paintDamageThreshold = 100;
    std::map<map::map_node*, float> _chances;
    std::map<map::map_node*, std::tuple<int, int>> _docks;
  };
}
}