#pragma once
#include <memory>
    
namespace kmint {
namespace pigisland {
    class shark;
}

namespace pigisland {
  class State {
    public:
      State() = default;
      virtual ~State() = default;
      virtual void sense();
      virtual void think() = 0;
      virtual void move() = 0;
      void setContext(shark*);
      void act();
      void checkSleep();
    //protected:
      bool hasSmelled;
      std::shared_ptr<shark> context;
  };
} //pigisland
} //kmint