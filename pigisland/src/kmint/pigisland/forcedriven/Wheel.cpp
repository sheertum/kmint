#include "kmint/pigisland/forcedriven/Wheel.h"
#include "kmint/pigisland/forcedriven/Vehicle.h"
#include "kmint/pigisland/forcedriven/Wall.h"

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

vector2d Wheel::seperate(const vector2d& neighbour, const vector2d& currentPosition) {
	vector2d toNeighbour = currentPosition - neighbour;
	return normalize(toNeighbour) / toNeighbour.length();
}


void Wheel::flock(const std::list<Agent>& neighbours, const Agent& actingAgent, double cohesion, double seperation, double alignment) {
	vector2d groupCenter{ 0,0 };
	vector2d seperationForce{ 0,0 };
	vector2d heading{0,0};
	int neighbourCount = 0;

	for (const auto& neighbour : neighbours) {
		neighbourCount++;
		groupCenter += neighbour.location;
		seperationForce += seperate(neighbour.location, actingAgent.location);
		heading += neighbour.vehicle.heading();
	}

	addForce(seperationForce * seperation);

	if (neighbourCount > 0)
	{
		//Cohesion
		if (cohesion != 0)
		{
			groupCenter /= neighbourCount;
			seek(groupCenter, actingAgent.vehicle, actingAgent.location, cohesion);
		}

		//alignment
		if (alignment != 0)
		{
			heading /= neighbourCount;
			heading -= actingAgent.vehicle.heading();
			addForce(heading * alignment);
		}
	}
}

void Wheel::avoidWall(const Agent& agent) {
	if (agent.vehicle.velocity().x() == 0 && agent.vehicle.velocity().y() == 0)
	{
		return;
	}

	Wall wall{ vector2d{16, 752}, vector2d{784, 752} };

	vector2d feeler = agent.vehicle.velocity();

	double distance;
	vector2d closestPoint;
	if (wall.intersect(agent.location, { agent.location + feeler }, distance, closestPoint)) {
		vector2d overshoot = feeler - closestPoint;

		vector2d normal{ 0,-1 };
		vector2d result = normal * overshoot.length();
		addForce(result);
	}
}
