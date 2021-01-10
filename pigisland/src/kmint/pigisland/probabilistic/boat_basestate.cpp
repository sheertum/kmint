#include "kmint/pigisland/probabilistic/boat_basestate.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/Evolution.hpp"

namespace kmint {
namespace pigisland {
    BaseState::BaseState(int paintJob, std::map<Node*, float> chances, std::map<map::map_node*, std::tuple<int, int>> docks) : _paintDamage{ paintJob }, _chances{ chances }, _docks{ docks }, _context{nullptr}, _stateColor{0,0,0} {}

  void BaseState::setdocks(map::map_graph& g){
    if(_chances.size() == 0){
      for(int i = 1; i < 4; i++){
        char number = i+'0';      
        auto dock = &find_node_of_kind(g, number);
        _chances.emplace(dock, 0.33);
      }
      auto docks = _chances.begin();
      _docks.emplace(docks->first, std::tuple<int, int>{30, 50});
      docks++;
      _docks.emplace(docks->first, std::tuple<int, int>{20, 100});
      docks++;
      _docks.emplace(docks->first, std::tuple<int, int>{50, 50});
    }
  }

  void BaseState::setContext(boat* context){
    _context = context;
    setColor();
  }

  void BaseState::setColor()
  {
      _context->getDrawable().set_tint(_stateColor);
  }

  void BaseState::increasePaintDamage(){
    if(_paintDamage < _paintDamageThreshold){
      _paintDamage++;
    }
  }

  void BaseState::repairPaintjob(int amount)
  {
    _paintDamage -= amount;
    if(_paintDamage < 0){
      _paintDamage = 0;
    }
  }

  void BaseState::boardPig(){
    for (auto i = _context->begin_collision(); i != _context->end_collision(); ++i) {
      if(typeid(*i) == typeid(pig)){
        Evolution::getInstance().addPig(((pig&)*i).data(), 4);
        i->remove();
      }
    }
  }

  void BaseState::calculateStepCost()
  {
    auto type = &_context->node().node_info().kind;
    if(*type == 'R')
    {
      _nextStepWeight = 4; 
    } 
    else 
    {
      _nextStepWeight = 1;
    }
  }

  int BaseState::getStepWeight()
  {
    return _nextStepWeight;
  }
}
}