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
    drawable_{ *this, pig_image() }, _dikkeBMW{0.1,60}{
    //_dikkeBMW._velocity = vector2d{ -60,-30 };
}

void pig::act(delta_time dt) {
    _dikkeBMW.takeTheWheel().flushForces();
    //_dikkeBMW.takeTheWheel().addForce(_dikkeBMW.resitanceVector(to_seconds(dt)));

    std::list<Agent> neighbours;

    for (auto i = begin_perceived(); i != end_perceived(); ++i) {
        auto const& a = *i;
        if (typeid(a) == typeid(pig))
        {
            _dikkeBMW.takeTheWheel().flee(a.location(), _dikkeBMW, play::free_roaming_actor::location());
            const pig&  piggy = (const pig&)a;
            neighbours.push_back(Agent{ a.location(), piggy.getVehicle()});
        }else if (typeid(a) == typeid(shark)) {
            _dikkeBMW.takeTheWheel().flee(a.location(), _dikkeBMW, location(), 300);
        }
        else if (typeid(a) == typeid(boat)) {
            _dikkeBMW.takeTheWheel().seek(a.location(), _dikkeBMW, location(), 150);
        }
    }

    _dikkeBMW.takeTheWheel().flock(neighbours, Agent{ location(), getVehicle() }, 1.5, 1, 5);
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
