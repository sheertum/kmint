#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/forcedriven/Wheel.h"
#include "kmint/pigisland/shark.hpp"

namespace kmint {
    using namespace math;
namespace pigisland {


pig::pig(math::vector2d location)
  : play::free_roaming_actor{location},
    drawable_{ *this, pig_image() }, _dikkeBMW{1,30}{
}

void pig::act(delta_time dt) {
    _dikkeBMW.takeTheWheel().flushForces();

    std::list<Agent> neighbours;

    for (auto i = begin_perceived(); i != end_perceived(); ++i) {
        auto const& a = *i;
        if (typeid(a) == typeid(pig))
        {
            _dikkeBMW.takeTheWheel().flee(a.location(), _dikkeBMW, play::free_roaming_actor::location());
            const pig&  piggy = (const pig&)a;
            neighbours.push_back(Agent{ a.location(), piggy.getVehicle()});
        }

        if (typeid(a) == typeid(shark)) {
            _dikkeBMW.takeTheWheel().flee(a.location(), _dikkeBMW, location(), 10);
        }

    }

    _dikkeBMW.takeTheWheel().flock(neighbours, Agent{ location(), getVehicle() }, 1, 2, 1);
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
