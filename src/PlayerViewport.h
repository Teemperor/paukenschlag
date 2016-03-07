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
#include <ui/PlayerStatus.h>
#include <sfbl/sfbl.h>

class Level;

class PlayerViewport {

    sf::RenderWindow& window_;
    sf::View view_;
    std::list<Effect> effects_;
    Level* level_;
    Character* player_;

    PlayerStatus status;

    std::unique_ptr<sfbl::WorldLight> worldLight_;

public:
    PlayerViewport(Level* level, sf::RenderWindow& window);

    virtual ~PlayerViewport();

    void renderUI();

    Character* player() {
        return player_;
    }

    void player(Character* player);

    void updateUI(double deltaT) {
        status.update(deltaT);
    }

    void apply();

    sf::View& view() {
        return view_;
    }

    sf::RenderWindow& window() {
        return window_;
    }

    Level& level() {
        return *level_;
    }

    void renderEffects(Level& level);

    void addEffect(Level& level, const EffectData& data);

    b2Vec2 centerPos() {
        return {view_.getCenter().x / SCALE, view_.getCenter().y / SCALE};
    }

};


#endif //SHOOTER_PLAYERVIEWPORT_H
