#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/forcedriven/Wheel.h"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/boat.hpp"

namespace kmint {
    using namespace math;
namespace pigisland {


pig::pig(math::vector2d location)
  : play::free_roaming_actor{location},
    drawable_{ *this, pig_image() }, _dikkeBMW{0.5,30},
    _wander{0, 0, 10},
    _wanderPig{ false },//(random_int(0,9) % 2),
    _cohesion{(uint16_t)random_int(1,0xFFFF + 1)},
    _seperation{ (uint16_t)random_int(1,0xFFFF + 1) },
    _alignment{ (uint16_t)random_int(1,0xFFFF + 1) },
    _sharkLikeNess{ (uint16_t)random_int(1,0xFFFF + 1) },
    _boatFetisj{ (uint16_t)random_int(1,0xFFFF + 1) }
{
    drawable_.set_tint(graphics::color{ (uint8_t)(255*_cohesion),(uint8_t)(255*_seperation),(uint8_t)(255*_alignment) });
}

pig::pig(math::vector2d location, uint16_t cohesion, uint16_t seperation, uint16_t alignment, uint16_t sharkLikeNess, uint16_t boatFetisj) :
    play::free_roaming_actor{ location },
    drawable_{ *this, pig_image() }, _dikkeBMW{ 0.5,30 },
    _wander{ 0, 0, 10 },
    _wanderPig{ false },//(random_int(0,9) % 2),
    _cohesion{ cohesion},
    _seperation{ seperation },
    _alignment{ alignment },
    _sharkLikeNess{ sharkLikeNess },
    _boatFetisj{ boatFetisj }
{
}

std::vector<uint16_t> pig::data() const {
    std::vector<uint16_t> result;
    result.resize(5);
    result[0] = _cohesion;
    result[1] = _seperation;
    result[2] = _alignment;
    result[3] = _sharkLikeNess;
    result[4] = _boatFetisj;

    return result;
}

double pig::toFleeSeekValue(uint16_t value) {
    uint16_t max = 0xFFFF/2;
    int32_t temp = value-max;
    return ((double)temp) / max;
}

void pig::act(delta_time dt) {
    _dikkeBMW.takeTheWheel().flushForces();

    std::list<Agent> neighbours;

    for (auto i = begin_perceived(); i != end_perceived(); ++i) {
        auto const& a = *i;
        if (typeid(a) == typeid(pig) && !_wanderPig)
        {
            _dikkeBMW.takeTheWheel().flee(a.location(), _dikkeBMW, play::free_roaming_actor::location());
            const pig&  piggy = (const pig&)a;
            neighbours.push_back(Agent{ a.location(), piggy.getVehicle()});
        }else if (typeid(a) == typeid(shark)) {
            _dikkeBMW.takeTheWheel().flee(a.location(), _dikkeBMW, location(), toFleeSeekValue(_sharkLikeNess));
        }
        else if (typeid(a) == typeid(boat)) {
            double result = ((int)_boatFetisj - (0xFFFF / 2)) / (0xFFFF / 2);
            _dikkeBMW.takeTheWheel().seek(a.location(), _dikkeBMW, location(), toFleeSeekValue(_boatFetisj));
        }
    }

    if (_wanderPig)
    {
        _dikkeBMW.takeTheWheel().addForce(_wander.wander(_dikkeBMW, location()));
    }
    else {
        double cohesion = _cohesion / 0xFFFF;
        double seperation = _seperation / 0xFFFF;
        double alignment = _alignment / 0xFFFF;

        _dikkeBMW.takeTheWheel().flock(neighbours, Agent{ location(), getVehicle() }, cohesion, seperation, alignment);
    }

    _dikkeBMW.takeTheWheel().avoidWall(Agent{ location(), getVehicle() });
    location(_dikkeBMW.updatePosition(to_seconds(dt), location()));
}

const Vehicle& pig::getVehicle() const {
    return _dikkeBMW;
}

Vehicle& pig::getVehicle() {
    return _dikkeBMW;
}

void pig::setData(const std::vector<uint16_t>& data) {
    _cohesion = data[0];
    _seperation = data[1];
    _alignment = data[2];
    _sharkLikeNess = data[3];
    _boatFetisj = data[4];
}

} // namespace pigisland

} // namespace kmint
