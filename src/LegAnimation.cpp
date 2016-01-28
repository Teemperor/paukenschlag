/*
 * Copyright 2015 WebAssembly Community Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "LegAnimation.h"
#include <Level.h>

void LegAnimation::render(const b2Vec2& pos, double rotation, PlayerViewport &viewport) {

    double legStretchFactor;
    switch(state_) {
        case State::Standing:
            legStretchFactor = 0;
            break;
        case State::Walking:
            legStretchFactor = std::cos(viewport.level().time() * 2);
            break;
        case State::Running:
            legStretchFactor = std::cos(viewport.level().time() * 12);
            break;
        default:
            assert(false);
    }

    sprite_.setScale((float) legStretchFactor * 1.4f, 1);


    sprite_.setPosition(SCALE * pos.x, SCALE * pos.y);
    sprite_.setRotation((float) (rotation * 180 / b2_pi));
    viewport.window().draw(sprite_);

}