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
    _cohesion{random_scalar(0,1)},
    _seperation{ random_scalar(0,1) },
    _alignment{ random_scalar(0,1) },
    _sharkLikeNess{ random_scalar(-1,1) },
    _boatFetisj{ random_scalar(-1,1) }
{
    drawable_.set_tint(graphics::color{ (uint8_t)(255*_cohesion),(uint8_t)(255*_seperation),(uint8_t)(255*_alignment) });
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
            _dikkeBMW.takeTheWheel().flee(a.location(), _dikkeBMW, location(), _sharkLikeNess);
        }
        else if (typeid(a) == typeid(boat)) {
            _dikkeBMW.takeTheWheel().seek(a.location(), _dikkeBMW, location(), _boatFetisj);
        }
    }

    if (_wanderPig)
    {
        _dikkeBMW.takeTheWheel().addForce(_wander.wander(_dikkeBMW, location()));
    }
    else {
        _dikkeBMW.takeTheWheel().flock(neighbours, Agent{ location(), getVehicle() }, _cohesion, _seperation, _alignment);
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

} // namespace pigisland

} // namespace kmint
