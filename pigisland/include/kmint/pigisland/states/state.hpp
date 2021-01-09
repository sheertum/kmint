#pragma once
#include "kmint/pigisland/AStar.h"
#include <memory>

namespace kmint {
namespace pigisland {
  class shark;

  class State {
    public:
      State(map::map_graph& graph);
      State(map::map_graph& graph, map::map_node* restTarget, int energy,  shark* context,  bool isScared);
      virtual ~State() = default;
      virtual void sense();
      virtual void think();
      virtual void move();
      virtual void setContext(shark*);
      virtual void collide();
      virtual void calculateNextStep() = 0;
      void calculateStepCost();
      void setNextStepOnPath();
      int getStepWeight();
      void createPath(Node*);
      void eat();
      void resetEnergy();
      std::unique_ptr<State> getNewState();
      std::unique_ptr<State>& gestState();
      std::unique_ptr<State> updateTransitionState(State* state);

      shark* context;

    protected:
      int _nextStepWeight = 0;
      std::list<Node*> _path;
      std::list<kmint::map::map_node *>::iterator _nextPathStep;
      map::map_graph& _graph;
      map::map_node* _smellTarget;
      map::map_node* _restTarget;
      map::map_node* _nextStep;

      bool _isScared;
      int _energy;
  };
} //pigisland
} //kmint