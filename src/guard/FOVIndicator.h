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


#ifndef SHOOTER_FOVINDICATOR_H
#define SHOOTER_FOVINDICATOR_H


#include <Box2D/Common/b2Math.h>
#include <PlayerViewport.h>

class FOVIndicator {

    sf::Sprite fovLimit_;

public:
    FOVIndicator() {
        fovLimit_ = TextureManager::instance().loadSprite("data/emotes/fovLimit.png");
        fovLimit_.setOrigin(0, fovLimit_.getLocalBounds().height);
    }

    void render(PlayerViewport& viewport, const b2Vec2& pos, double direction, double angle) {
        fovLimit_.setPosition(pos.x * SCALE, pos.y * SCALE);
        fovLimit_.setScale(1, 1);
        fovLimit_.setRotation((float) ((direction + angle / 2) * 180 / b2_pi));
        viewport.window().draw(fovLimit_);

        fovLimit_.setScale(1, -1);
        fovLimit_.setRotation((float) ((direction - angle / 2) * 180 / b2_pi));
        viewport.window().draw(fovLimit_);
    }
};


#endif //SHOOTER_FOVINDICATOR_H
