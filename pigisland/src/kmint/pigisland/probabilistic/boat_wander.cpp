#include "kmint/pigisland/probabilistic/boat_wander.hpp"
#include "kmint/pigisland/probabilistic/boat_repair.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
namespace pigisland {
	BoatWanderState::BoatWanderState(int paintJob, std::map<Node*, float> chances, std::map<map::map_node*, std::tuple<int, int>> docks) : BaseState(paintJob, chances, docks) {}
	
	BoatWanderState::BoatWanderState() : BaseState(0, std::map<Node*, float> {}, std::map<map::map_node*, std::tuple<int, int>> {}) {}

	void BoatWanderState::move() {
		int next_index = random_int(0, _context->node().num_edges());
		_context->node(_context->node()[next_index].to());
		increasePaintDamage();
	}

	void BoatWanderState::sense() {
		calculateStepCost();
		if(_paintDamage == _paintDamageThreshold){
			auto newState = std::make_unique<BoatRepairState>(_paintDamage, _chances, _docks);
			_context->changeState(std::move(newState));
		}
	}
}
}