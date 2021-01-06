#include "..\..\..\..\include\kmint\pigisland\states\wanderState.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
namespace pigisland {
  WanderingState::WanderingState(std::shared_ptr<shark> actor) : State{ actor } {}

  void WanderingState::sense()
  {
    bool smelledPork = false;
    for (auto i = context->begin_perceived(); i != context->end_perceived(); ++i) {
      auto const& a = *i;
      auto distance = sqrt(a.location().x() * a.location().x() + a.location().y() * a.location().y());
      if (distance > 100) {
        smelledPork = true;
      }
    }
  }

  void WanderingState::think()
  {
  }

  void WanderingState::move()
  {
    int next_index = random_int(0, context->node().num_edges());
    context->node(context->node()[next_index].to());
  }
}
}