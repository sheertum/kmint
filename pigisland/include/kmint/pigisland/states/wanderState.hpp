#pragma once

#include "state.hpp"

namespace kmint {
namespace pigisland {
    class WanderingState : public State {
    public:
        WanderingState(std::shared_ptr<shark>);
        virtual ~WanderingState() = default;
        void sense() override;
        void think() override;
        void move() override;
    };
}
}