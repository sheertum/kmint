#pragma once

#include "kmint/math/vector2d.hpp"

#include <vector>

class Wall {
	using vec = kmint::math::vector2d;
public:
	Wall(const vec& from, const vec& to);

	bool intersect(const vec& position, const std::vector<vec>& feelers, double& distance, vec& intersectionPoint);

private:
	bool inBound(const vec& target, const vec& position1, const vec& position2);
	bool inBound(float target, float position1, float position2);

private:
	vec _from, _to;
};