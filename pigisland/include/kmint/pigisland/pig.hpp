#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include "forcedriven/Vehicle.h"

#include <tuple>
#include <vector>

namespace kmint {
namespace pigisland {

class pig : public play::free_roaming_actor {
public:
  pig(math::vector2d location);
  const ui::drawable &drawable() const override { return drawable_; }

  void act(delta_time dt) override;

  bool perceptive() const override { return true; }
  scalar perception_range() const override { return 1000.f; }
  bool incorporeal() const override { return false; }

private:
  play::image_drawable drawable_;
  Vehicle _dikkeBMW;
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
