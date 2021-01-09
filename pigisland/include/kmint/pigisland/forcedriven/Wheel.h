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
	kmint::math::vector2d exponatial(const kmint::math::vector2d& current, const kmint::math::vector2d& max, double lowestDivider = std::numeric_limits<double>::denorm_min(), double toDivide = 1) const;
	double exponatial(double current, double max, double lowestDivider = std::numeric_limits<double>::denorm_min(), double toDivide = 1) const;

private:
	std::vector<kmint::math::vector2d> _forces;
	const float FEELER_LENGTH{ 16 };
};
