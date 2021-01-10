#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include "forcedriven/Vehicle.h"
#include "forcedriven/Wander.h"

#include <tuple>
#include <vector>

namespace kmint {
namespace pigisland {

class pig : public play::free_roaming_actor {
public:
  pig(math::vector2d location);
  pig(math::vector2d location, uint16_t cohesion, uint16_t seperation, uint16_t alignment, uint16_t sharkLikeNess, uint16_t boatFetisj);
  const ui::drawable &drawable() const override { return drawable_; }

  void act(delta_time dt) override;

  bool perceptive() const override { return true; }
  scalar perception_range() const override { return 100.0f; }
  bool incorporeal() const override { return false; }
  scalar collision_range() const override { return 16.0; }

  const Vehicle& getVehicle() const;
  Vehicle& getVehicle();

  void setData(const std::vector<uint16_t>& data);

  std::vector<uint16_t> data() const override;

  static double toFleeSeekValue(uint16_t value);

  uint16_t _cohesion, _seperation, _alignment, _sharkLikeNess, _boatFetisj;
private:
  bool _wanderPig;
  play::image_drawable drawable_;
  Vehicle _dikkeBMW;
  Wander _wander;
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
