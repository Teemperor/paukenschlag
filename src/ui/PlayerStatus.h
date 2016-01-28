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


#ifndef SHOOTER_PLAYERSTATUS_H
#define SHOOTER_PLAYERSTATUS_H

#include <SFML/Graphics/Sprite.hpp>
#include <TextureManager.h>

class Character;

class PlayerStatus {

    sf::Sprite itemCircle;
    float radius = 48;
    Character* character;

public:
    PlayerStatus(Character* character = nullptr) : character(character) {
        itemCircle = TextureManager::instance().loadSprite("data/ui/itemCircle.png");
        itemCircle.setOrigin(itemCircle.getLocalBounds().width / 2, itemCircle.getLocalBounds().height / 2);
    }

    void draw(sf::RenderTarget& target, float x, float y);

    void update(double deltaT) {

    }

};

#endif //SHOOTER_PLAYERSTATUS_H
