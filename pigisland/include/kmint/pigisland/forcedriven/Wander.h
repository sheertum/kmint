#pragma once

#include "kmint/math/vector2d.hpp"
#include "Vehicle.h"

class Wander {
public:
	Wander(float radius, float distance, float jitter);
	Wander() = default;

	kmint::math::vector2d wander(const Vehicle&, const kmint::math::vector2d& position);

private:
	float _radius;
	float _distance;
	float _jitter;
	kmint::math::vector2d _target;
};