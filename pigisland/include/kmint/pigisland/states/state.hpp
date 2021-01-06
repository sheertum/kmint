#pragma once
#include <memory>
    
namespace kmint {
namespace pigisland {
    class shark;
}

namespace pigisland {

  class State {
    public:
      State(std::shared_ptr<shark>);
      virtual ~State() = default;
      virtual void sense() = 0;
      virtual void think() = 0;
      virtual void move() = 0;
      void act();
      void checkSleep();
    protected:
      std::shared_ptr<shark> context;
  };
} //pigisland
} //kmint