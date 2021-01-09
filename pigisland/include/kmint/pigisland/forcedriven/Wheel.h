#pragma once
#include "kmint/math/vector2d.hpp"
#include <vector>
#include <list>

class Vehicle;

struct Agent
{
	const kmint::math::vector2d& location;
	const Vehicle& vehicle;
};

class Wheel {
public:
	void addForce(const kmint::math::vector2d&);

	kmint::math::vector2d forceSum() const;
	void flushForces();

	void seek(const kmint::math::vector2d& targetPosition, const Vehicle& vehicle, const kmint::math::vector2d& currentPosition, double factor = 1);
	void flee(const kmint::math::vector2d& targetPosition, const Vehicle& vehicle, const kmint::math::vector2d& currentPosition, double factor = 1);
	
	kmint::math::vector2d seperate(const kmint::math::vector2d& neighbours, const kmint::math::vector2d& currentPosition);
	
	void flock(const std::list<Agent>& neighbours, const Agent& actingAgent, double cohesion = 1, double seperation = 1, double alignment = 1);
	
	void avoidWall(const Agent&);


private:
	std::vector<kmint::math::vector2d> _forces;
};
