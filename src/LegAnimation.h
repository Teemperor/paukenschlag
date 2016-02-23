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


#ifndef SHOOTER_LEGANIMATION_H
#define SHOOTER_LEGANIMATION_H


#include <SFML/Graphics/Sprite.hpp>
#include "PlayerViewport.h"

class LegAnimation {

    sf::Sprite sprite_;

public:
    enum State {
        Walking,
        Running,
        Standing
    };
private:
    State state_ = State::Standing;

public:

    LegAnimation(const std::string& path, int ox, int oy) {
        sprite_ = TextureManager::instance().loadSprite(path);
        sprite_.setOrigin(ox, oy);
    }

    void state(State state) {
        state_ = state;
    }

    void render(const b2Vec2& pos, double rotation, PlayerViewport &viewport, double alpha);
};


#endif //SHOOTER_LEGANIMATION_H
