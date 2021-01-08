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
    drawable_{ *this, pig_image() }, _dikkeBMW{1,10}{
    //_dikkeBMW.takeTheWheel().seek(vector2d{ 10,10 }, _dikkeBMW, play::free_roaming_actor::location());
    //_dikkeBMW.takeTheWheel().flee(vector2d{ 100,100 }, _dikkeBMW, play::free_roaming_actor::location());
}

void pig::act(delta_time dt) {
    _dikkeBMW.takeTheWheel().flushForces();

    for (auto i = begin_perceived(); i != end_perceived(); ++i) {
        auto const& a = *i;
        if (typeid(a) == typeid(shark))
        {
            _dikkeBMW.takeTheWheel().flee(a.location(), _dikkeBMW, play::free_roaming_actor::location());
            //std::cout << "Smelled a shark at " << a.location().x() << ", "
            //    << a.location().y() << "\n";
        }

    }

    location(_dikkeBMW.updatePosition(to_seconds(dt), location()));
}

} // namespace pigisland

} // namespace kmint
