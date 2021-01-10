#include "kmint/pigisland/forcedriven/Vehicle.h"
#include "kmint/pigisland/forcedriven/Wheel.h"

using namespace kmint::math;

Vehicle::Vehicle(double mass, double maxSpeed, const kmint::math::vector2d& startingVelocity) :
_mass{mass},
_maxSpeed{maxSpeed},
_velocity{startingVelocity},
_heading{ vector2d{0,1} }
{
	updateHeading();
}

vector2d Vehicle::updatePosition(double dt, const kmint::math::vector2d& currentPosition)
{
	vector2d steeringForce = _wheel.forceSum();
	vector2d acceleration = steeringForce / _mass;

	_velocity += acceleration * dt;
	truncateVelocity(_maxSpeed);

	updateHeading();

	return currentPosition + (_velocity*dt);
}

void Vehicle::truncateVelocity(double max) {
	if (_velocity.length() > max)
	{
		_velocity = normalize(_velocity) * max;
	}
}

void Vehicle::updateHeading() {
	if (_velocity.length() > 0.00001)
	{
		_heading = normalize(_velocity);
		_right = rotate(_heading, angle{ pi / 2 });
	}
}

const Wheel& Vehicle::takeTheWheel() const {
	return _wheel;
}

Wheel& Vehicle::takeTheWheel() {
	return _wheel;
}

double Vehicle::maxSpeed() const {
	return _maxSpeed;
}

const vector2d& Vehicle::velocity() const {
	return _velocity;
}

const vector2d& Vehicle::heading() const {
	return _heading;
}

const vector2d& Vehicle::side() const {
	return _right;
}

vector2d Vehicle::resitanceVector(double dt) const {
	return (_velocity * _resistance * dt * -1)/_mass;
}

double Vehicle::mass() const {
	return _mass;
}