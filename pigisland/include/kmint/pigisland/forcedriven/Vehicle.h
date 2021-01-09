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

	kmint::math::vector2d resitanceVector(double dt) const;

	double mass() const;

	kmint::math::vector2d _velocity;

private:
	void updateHeading();

private:
	double _mass;
	double _maxSpeed;
	double _resistance{300000};
	kmint::math::vector2d _heading;
	kmint::math::vector2d _right;
	Wheel _wheel;
};