#pragma once
#include "kmint/pigisland/AStar.h"
#include <memory>
    
namespace kmint {
namespace pigisland {
  class shark;

  class State {
    public:
      State() = default;
      virtual ~State() = default;
      virtual void sense();
      virtual void think();
      virtual void move() = 0;
      virtual void setContext(shark*);
      virtual void collide();
      void moveToTarget();
      void setPath(Node*);
      void eat();
      shark* context;
    protected:
      std::list<Node*> _path;
      std::list<kmint::map::map_node *>::iterator _nextStep;
      void wander();
  };
} //pigisland
} //kmint