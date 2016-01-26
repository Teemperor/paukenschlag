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


#ifndef SHOOTER_PLAYERVIEWPORT_H
#define SHOOTER_PLAYERVIEWPORT_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "Effect.h"
#include <list>

class Level;

class PlayerViewport {

    sf::RenderWindow& window_;
    sf::View view_;
    std::list<Effect> effects_;

public:
    PlayerViewport(sf::RenderWindow& window) : window_(window),
                                               view_(sf::Vector2f(window_.getSize().x / 2, window_.getSize().y / 2),
                                                     sf::Vector2f(window_.getSize().x, window_.getSize().y)
    ) {

    }

    void apply() {
        window_.setView(view_);
    }

    sf::View& view() {
        return view_;
    }

    sf::RenderWindow& window() {
        return window_;
    }

    void renderEffects(Level& level);

    void addEffect(Level& level, b2Vec2 point, float rotation);

};


#endif //SHOOTER_PLAYERVIEWPORT_H
