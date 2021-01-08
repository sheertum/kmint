#pragma once
#include "kmint/math/vector2d.hpp"
#include <vector>

class Vehicle;

class Wheel {
public:
	void addForce(const kmint::math::vector2d&);

	kmint::math::vector2d forceSum() const;
	void flushForces();

	void seek(const kmint::math::vector2d& targetPosition, const Vehicle& vehicle, const kmint::math::vector2d& currentPosition, double factor = 1);
	void flee(const kmint::math::vector2d& targetPosition, const Vehicle& vehicle, const kmint::math::vector2d& currentPosition, double factor = 1);

private:
	std::vector<kmint::math::vector2d> _forces;
};
