#pragma once

#include "kmint/math/vector2d.hpp"

#include <vector>

class Wall {
	using vec = kmint::math::vector2d;
public:
	Wall(const vec& from, const vec& to, const vec& normal);
	Wall() = default;

	bool intersect(const vec& position, const std::vector<vec>& feelers, double& distance, vec& intersectionPoint) const;

	vec normal() const;

	vec from() const;
	vec to() const;

private:
	bool inBound(const vec& target, const vec& position1, const vec& position2) const;
	bool inBound(float target, float position1, float position2) const;

private:
	vec _from, _to, _normal;
	static const int STEP_SIZE = 32;
	static const int OFFSET = 16;
};