#pragma once
#include "kmint/math/vector2d.hpp"
#include "Wheel.h"

class Vehicle {
public:
	Vehicle(double mass, double maxSpeed, const kmint::math::vector2d& startingVelocity = kmint::math::vector2d{ 0,0 });

	kmint::math::vector2d updatePosition(double dt, const kmint::math::vector2d& currentPosition);
	void truncateVelocity(double max);
	
	double maxSpeed() const;
	const kmint::math::vector2d& velocity() const;

	Wheel& takeTheWheel();
	const Wheel& takeTheWheel() const;

	const kmint::math::vector2d& heading() const;

private:
	void updateHeading();

private:
	double _mass;
	double _maxSpeed;
	kmint::math::vector2d _velocity;
	kmint::math::vector2d _heading;
	kmint::math::vector2d _right;
	Wheel _wheel;
};