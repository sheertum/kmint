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
    _wanderPig(random_int(0,9) % 2)
{
    if (_wanderPig)
    {
        drawable_.set_tint(graphics::color{ 255,0,0 });
    }
    else {
        //if (random_int(0, 4) == 3) {
        //    _dikkeBMW._velocity = vector2d{ 30,5 };
        //}
        //else {
        //    _dikkeBMW._velocity = vector2d{ 30,30 };
        //}
        _dikkeBMW.updateHeading();
        drawable_.set_tint(graphics::color{ 0,255,0 });
    }
}

void pig::act(delta_time dt) {
    _dikkeBMW.takeTheWheel().flushForces();
    //_dikkeBMW.takeTheWheel().addForce(_dikkeBMW.resitanceVector(to_seconds(dt)));

    std::list<Agent> neighbours;

    for (auto i = begin_perceived(); i != end_perceived(); ++i) {
        auto const& a = *i;
        if (typeid(a) == typeid(pig) && !_wanderPig)
        {
            _dikkeBMW.takeTheWheel().flee(a.location(), _dikkeBMW, play::free_roaming_actor::location());
            const pig&  piggy = (const pig&)a;
            neighbours.push_back(Agent{ a.location(), piggy.getVehicle()});
        }else if (typeid(a) == typeid(shark)) {
            _dikkeBMW.takeTheWheel().flee(a.location(), _dikkeBMW, location(), 1);
        }
        else if (typeid(a) == typeid(boat)) {
            _dikkeBMW.takeTheWheel().seek(a.location(), _dikkeBMW, location(), 1);
        }
    }

    if (_wanderPig)
    {
        _dikkeBMW.takeTheWheel().addForce(_wander.wander(_dikkeBMW, location()));
    }
    else {
        _dikkeBMW.takeTheWheel().flock(neighbours, Agent{ location(), getVehicle() }, 0, 1, 1);
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
