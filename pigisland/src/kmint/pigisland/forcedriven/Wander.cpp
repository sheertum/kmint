#include "kmint/pigisland/forcedriven/Wander.h"
#include "kmint/random.hpp"
#include <vector>
#include <iostream>
#include <string>

using namespace kmint::math;
using namespace kmint;

#define Matrix std::vector<std::vector<float>>

void print(const Matrix& m) {
	std::string result[3];

	for (const auto& vector : m) {
		int i = 0;
		for (const auto& value : vector) {
			result[i] += (std::to_string(value) + "\t");
			i++;
		}
	}

	for (size_t i = 0; i < 3; i++)
	{
		std::cout << result[i] << std::endl;
	}
}

void init(Matrix& m, size_t width, size_t height) {
	m.resize(width);
	for (auto& matrix : m) {
		matrix.resize(width, 0);
	}
}

Matrix multiply(const Matrix& m1, const Matrix& m2) {
	Matrix result;
	init(result, 3, 3);
	int x = 0;

	for (size_t i = 0; i < 3; i++)
	{
		result[0][0] += m1[i][0] * m2[0][i];
		result[1][0] += m1[i][0] * m2[1][i];
		result[2][0] += m1[i][0] * m2[2][i];

		result[0][1] += m1[i][1] * m2[0][i];
		result[1][1] += m1[i][1] * m2[1][i];
		result[2][1] += m1[i][1] * m2[2][i];

		result[0][2] += m1[i][2] * m2[0][i];
		result[1][2] += m1[i][2] * m2[1][i];
		result[2][2] += m1[i][2] * m2[2][i];
	}

	return result;
}

Matrix xToY(const Matrix& m) {
	Matrix result;
	init(result, 3, 3);

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			result[i][j] = m[j][i];
		}
	}

	return result;
}

Matrix rotate(const Matrix& m, const vector2d& forward, const vector2d& side) {
	Matrix translate;
	init(translate, 3, 3);

	translate[0][0] = forward.x();
	translate[0][1] = forward.y();

	translate[1][0] = side.x();
	translate[1][1] = side.y();

	translate[2][2] = 1;

	return multiply(m, translate);
}

Matrix translate(const Matrix& target, double x, double y) {
	Matrix m;
	init(m,3,3);
	for (size_t i = 0; i < 2; i++)
	{
		m[i][i] = 1;
	}

	m[2][0] = x;
	m[2][1] = y;

	return multiply(target, m);
}

vector2d transform(const Matrix& m, const vector2d& v) {
	vector2d result;
	result.x(m[0][0] * v.x() + m[1][0] * v.y() + m[2][0]);
	result.y(m[0][1] * v.x() + m[1][1] * v.y() + m[2][1]);
	return result;
}

vector2d pointToWorldSpace(	const vector2d& point,
							const vector2d& agentHeading,
							const vector2d& agentSide,
							const vector2d& agentPosition) {
	
	vector2d transformationPoint = point;
	Matrix matrix;
	init(matrix, 3, 3);
	for (size_t i = 0; i < 2; i++)
	{
		matrix[i][i] = 1;
	}

	matrix = rotate(matrix, agentHeading, agentSide);
	//print(matrix);
	matrix = translate(matrix, agentPosition.x(), agentPosition.y());

	return transform(matrix, point);
}

Wander::Wander(float radius, float distance, float jitter) :
	_radius{radius},
	_distance{distance},
	_jitter{jitter},
	_target{0,0}
{
}

vector2d Wander::wander(const Vehicle& vehicle, const kmint::math::vector2d& position)
{
	_target += vector2d{ random_scalar(-1, 1) * _jitter,
							random_scalar(-1, 1) * _jitter };



	return _target;//worldTarget - position;
}
