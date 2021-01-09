#include "kmint/pigisland/forcedriven/Wall.h"

using namespace kmint::math;

Wall::Wall(const vec& from, const vec& to, const vector2d& normal) :
_from{from * STEP_SIZE},
_to{to * STEP_SIZE },
_normal{ normal }
{
	_from += vec{ OFFSET,OFFSET };
	_to += vec{ OFFSET,OFFSET };
	_normal = normalize(normal);
}

//A = from
//B = to
//C = position
//D = line
//first = x
//second = y
bool Wall::intersect(const vec& position, const std::vector<vec>& feelers, double& distance, vec& intersectionPoint) const
{
	distance = std::numeric_limits<double>::infinity();

	vec line = feelers[0];

	float a1 = _to.y() - _from.y();
	float b1 = _from.x() - _to.x();
	float c1 = a1 * (_from.x()) + b1 * (_from.y());

	float a2 = line.y() - position.y();
	float b2 = position.x() - line.x();
	float c2 = a2 * (position.x()) + b2 * (position.y());

	float determinant = a1 * b2 - a2 * b1;

	if (determinant == 0)
	{
		return false;
	}

	intersectionPoint.x((b2 * c1 - b1 * c2) / determinant);
	intersectionPoint.y((a1 * c2 - a2 * c1) / determinant);

	if (!inBound(intersectionPoint,position,line) || !inBound(intersectionPoint,_from,_to))
	{
		return false;
	}

	distance = (position - intersectionPoint).length();


	return true;
}

bool Wall::inBound(float target, float position1, float position2) const{
	float max = (position1 > position2) ? position1 : position2;
	float min = (position1 < position2) ? position1 : position2;

	return (target <= max && target >= min);
}

bool Wall::inBound(const vec& target, const vec& position1, const vec& position2) const{
	return	inBound(target.x(), position1.x(), position2.x()) &&
			inBound(target.y(), position1.y(), position2.y());
}

vector2d Wall::normal() const {
	return _normal;
}

vector2d Wall::from() const {
	vec result = _from;
	result -= vec{ 16, 16 };
	result /= 32;
	return result;
}

vector2d Wall::to() const {
	vec result = _to;
	result -= vec{ 16, 16 };
	result /= 32;
	return result;
}