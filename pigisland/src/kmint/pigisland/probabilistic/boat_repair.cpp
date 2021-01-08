#include "kmint/pigisland/probabilistic/boat_repair.hpp"
#include "kmint/pigisland/probabilistic/boat_wander.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
namespace pigisland {
	BoatRepairState::BoatRepairState(int paintJob, std::map<Node*, float> chances, std::map<map::map_node*, std::tuple<int, int>> docks) : BaseState(paintJob, chances, docks), _path{}, _pickedDock{}, _nextStep{} {
		_pickedDock = pickDock();
	}
  
	void BoatRepairState::move() {
		moveToDock();
		if (_nextStep != _path.begin()) {
			_nextStep--;
		}
		else {
			repair();
		}
	}

	void BoatRepairState::sense() {
		if(_paintDamage != _paintDamageThreshold){
			_context->changeState(std::make_unique<BoatWanderState>(_paintDamage, _chances, _docks));
		}
	}

	void BoatRepairState::moveToDock(){
		if(_path.size() == 0){
			setPath();
		}
		auto node = *_nextStep;
		node->tagged(false);
		_context->node(*node);
	}

	map::map_node* BoatRepairState::pickDock(){
		float chance = random_scalar(0,1);
		float limit = 0;

		for(auto& dock : _chances){
			if(chance <= dock.second+limit && chance > limit){
				std::cout << "picked: " << std::endl;
				std::cout << "dock-x: " << dock.first->location().x() << std::endl;
				std::cout << "dock-y: " << dock.first->location().y() << std::endl;

				return dock.first;
			} 
			else {
				limit += dock.second;
			}
		}
	}

	void BoatRepairState::setPath(){
		bool found;
		_path = AStar::getPath(_context->node(), *_pickedDock, found);
		_nextStep = _path.end();
		_nextStep--;
	}

	void BoatRepairState::repair(){
		auto range = _docks[_pickedDock];
		int repairAmount;

		if (std::get<0>(range) == std::get<1>(range)) {
			repairAmount = std::get<0>(range);
		}
		else {
			repairAmount = random_int(std::get<0>(range), std::get<1>(range));
		}
		_paintDamage -= repairAmount;
		std::cout << "repairamount: " << repairAmount << std::endl;
		updateDock(repairAmount);
	}

	void BoatRepairState::updateDock(int repairAmount){
		float chanceIncrease;
		float chanceDecrease;
		
		if(repairAmount >= 50){
			chanceIncrease = 0.01;
		} 
		else {
			chanceIncrease = -0.01;
		}

		if (repairAmount > 60 || repairAmount < 40) {
			chanceIncrease *= 2;
		}

		if (repairAmount > 80 || repairAmount < 20) {
			chanceIncrease *= 2;
		}

		chanceDecrease = -1*chanceIncrease/(_chances.size()-1);

		for(auto& doc : _chances){
			if(doc.first == _pickedDock){
				if (doc.second == 1) {
					return;
				}
				doc.second += chanceIncrease;
			}
			else {
				if (doc.second == 0) {
					continue;
				}
				doc.second += chanceDecrease;
			}

			std::cout << "dock-x: " << doc.first->location().x() << std::endl;
			std::cout << "dock-y: " << doc.first->location().y() << std::endl;
			std::cout << "chance changed to: " << doc.second << std::endl;
		}
	}
}
}