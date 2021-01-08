#pragma once
#include "kmint/pigisland/AStar.h"
#include <memory>

namespace kmint {
namespace pigisland {
  class shark;

  class State {
    public:
      State(map::map_graph& graph);
      State(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context);
      virtual ~State() = default;
      virtual void sense();
      virtual void think();
      virtual void move() = 0;
      virtual void setContext(shark*);
      virtual void collide();
      void setNextStepOnPath();
      void createPath(Node*);
      void eat();
      void resetEnergy();
      map::map_node* getSmellTarget();
      bool hasSmell();
      bool isScared();
      int getEnergy();
      shark* context;
      std::unique_ptr<State> getNewState();
      std::unique_ptr<State>& gestState();
      map::map_node* getRestTarget() { return _restTarget; }
      map::map_graph& getGraph();
      std::unique_ptr<State> updateTransitionState(State* state);

    protected:
      void wander();

      std::list<Node*> _path;
      std::list<kmint::map::map_node *>::iterator _nextStep;
      map::map_graph& _graph;
      map::map_node* _smellTarget;
      map::map_node* _restTarget;

      bool _isScared;
      int _energy;
  };
} //pigisland
} //kmint