#include "kmint/pigisland/forcedriven/Wheel.h"
#include "kmint/pigisland/forcedriven/Vehicle.h"
#include<numeric>

using namespace kmint::math;
void Wheel::addForce(const vector2d& force) {
	_forces.push_back(force);
}

vector2d Wheel::forceSum() const {
	vector2d sum{ 0,0 };

	for (auto const& it : _forces) {
		sum += it;
	}
	
	return sum;
}

void Wheel::seek(const vector2d& targetPosition, const Vehicle& vehicle, const kmint::math::vector2d& currentPosition, double factor){
	vector2d desiredVelocity = normalize(targetPosition - currentPosition) * vehicle.maxSpeed();
	addForce((desiredVelocity - vehicle.velocity()) * factor);
}

void Wheel::flee(const kmint::math::vector2d& targetPosition, const Vehicle& vehicle, const kmint::math::vector2d& currentPosition, double factor) {
	vector2d desiredVelocity = normalize(currentPosition - targetPosition) * vehicle.maxSpeed();
	addForce((desiredVelocity - vehicle.velocity()) * factor);
}

void Wheel::flushForces() {
	_forces.clear();
}