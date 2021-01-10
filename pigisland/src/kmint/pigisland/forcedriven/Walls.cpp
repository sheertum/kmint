#include "kmint/pigisland/forcedriven/Walls.h"

#define v kmint::math::vector2d

std::vector<Wall> Walls::getWalls()
{
	static std::vector<Wall> walls{ Wall{v{0,23},	v{24,23},	v{0,1}},
									Wall{v{24,23},	v{24,19},	v{-1, 0}},
									Wall{v{24,19},	v{28,16},	v{-3,4}},
									Wall{v{28,16},	v{31,16},	v{0, 1}},
									Wall{v{31,16},	v{31,4},	v{-1, 0}},
									Wall{v{31,4},	v{27,0},	v{4,-4}},
									Wall{v{9,0},	v{27,0},	v{0, -1}},
									Wall{v{9,0},	v{9,2},		v{1, 0}},
									Wall{v{9,2},	v{0,3},		v{1, -9}},
									Wall{v{0,3},	v{0,23},	v{1, 0}},
									Wall{v{2,21},	v{5,21},	v{0,-1}},
									Wall{v{5,21},	v{7,17},	v{4,-2}},
									Wall{v{7,17},	v{2,17},	v{0,1}},
									Wall{v{2,17},	v{2,21},	v{-1,0}} };
	return walls;
}
