#include "kmint/pigisland/forcedriven/Wheel.h"
#include "kmint/pigisland/forcedriven/Vehicle.h"
//#include "kmint/pigisland/forcedriven/Wall.h"
#include "kmint/pigisland/forcedriven/Walls.h"
#include "kmint/math/angle.hpp"

#include <iostream>
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
	addForce((desiredVelocity - vehicle.velocity()) * toFleeSeekValue(factor));
}

void Wheel::flee(const kmint::math::vector2d& targetPosition, const Vehicle& vehicle, const kmint::math::vector2d& currentPosition, double factor) {
	vector2d desiredVelocity = normalize(currentPosition - targetPosition) * vehicle.maxSpeed();
	addForce((desiredVelocity - vehicle.velocity()) * toFleeSeekValue(factor));
}

double Wheel::toFleeSeekValue(double factor) const {
	if (std::abs(factor) > 1)
	{
		factor /= std::abs(factor);
	}
	return (1 / (1.00001 - factor)) * factor;
}

void Wheel::flushForces() {
	_forces.clear();
}

vector2d Wheel::seperate(const vector2d& neighbour, const vector2d& currentPosition) {
	vector2d toNeighbour = currentPosition - neighbour;
	return normalize(toNeighbour) / toNeighbour.length();
}

double Wheel::toFlockingValue(double value) const{
	if (value > 1)
	{
		value = 1;
	}
	return (1 / (1.001 - value))*value;
}

void Wheel::flock(const std::list<Agent>& neighbours, const Agent& actingAgent, double cohesion, double seperation, double alignment) {
	cohesion = toFlockingValue(cohesion);
	seperation = toFlockingValue(seperation);
	alignment = toFlockingValue(alignment);

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

	vector2d h = normalize(agent.vehicle.velocity());
	std::vector<vector2d> feelers = {	rotate(h, angle::from_degrees(-60)) * FEELER_LENGTH,
										h * FEELER_LENGTH,	
										rotate(h, angle::from_degrees(60)) * FEELER_LENGTH };

	for (const auto& feeler : feelers) {
		Wall closestWall;
		vector2d closestPoint{ 0,0 };
		double closestDistance = std::numeric_limits<double>::infinity();

		for (auto& wall : Walls::getWalls()) {
			double distance;
			vector2d point;

			if (wall.intersect(agent.location, { agent.location + feeler }, distance, point)) {

				if (distance < closestDistance)
				{
					closestDistance = distance;
					closestWall = wall;
					closestPoint = point;
				}
			}
		}

		if (closestDistance < std::numeric_limits<double>::infinity()) {
			vector2d overshoot = (agent.location + feeler) - closestPoint;
			vector2d normal = closestWall.normal();
			normal.y(normal.y() * -1);
			vector2d result = normal * (std::pow(overshoot.length() * overshoot.length(), 2)) * agent.vehicle.mass();

			if (FEELER_LENGTH - overshoot.length() < 5)
			{
				flushForces();
			}
			addForce(result);
			//std::cout << result.x() << "\t" << result.y() << "\t" << overshoot.length() << "\t" << closestWall.from() <<  "\t" << closestWall.to() << '\n';
		}
	}


}

vector2d Wheel::exponatial(const kmint::math::vector2d& current, const kmint::math::vector2d& max, double lowestDivider, double toDivide) const{
	double divider = (max - current).length();
	if (divider <= lowestDivider)
	{
		divider = lowestDivider;
	}

	return (normalize(current)*(toDivide / divider));
}

double Wheel::exponatial(double current, double max, double lowestDivider, double toDivide) const {
	double maxResult = 9999;
	double result = 1 / max - current;
	return (result > maxResult) ? maxResult : result;
}