#pragma once
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
      void setContext(shark*);
      void act();
      shark* context;
    protected:
      void wander();
  };
} //pigisland
} //kmint