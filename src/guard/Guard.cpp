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


#include <Hideaway.h>
#include "Guard.h"
#include "Character.h"
#include "Utils.h"


void Guard::update(Level& level, double deltaT) {

    if (usedHideaways != 0) {
        bool playerNear = false;

        for (Character* player : level.players()) {
            if (Utils::distance(player->position(), position()) < 5) {
                playerNear = true;
            }
        }
        if (!playerNear)
            visible_ = false;
    }

    Utils::animateTo(alpha_, visible_ ? 1 : 0, deltaT, 3);

    if (!dead_) {
        suspicionIndicator_.update(level, deltaT);

        ai_.update(*this, level, deltaT);
        double headRotationDiff = headRotationTarget - headRotation;

        double headRotationChange = deltaT;

        if (std::abs(headRotationDiff) < headRotationChange) {
            headRotation = headRotationTarget;
        } else {
            if (headRotationTarget > headRotation) {
                headRotation += headRotationChange;
            } else {
                headRotation -= headRotationChange;
            }
        }
    }
}

void Guard::shoot(b2Vec2 target) {
    weapon().tryUse(level(), position(), target);
}

void Guard::initBodyAnimation() {
    sf::Sprite idleSprite = TextureManager::instance().loadSprite("data/guard/idle.png");
    idleSprite.setOrigin(20, 20);
    bodyAnimation_.idleSprite(idleSprite);

    sf::Sprite pistolSprite = TextureManager::instance().loadSprite("data/guard/pistol.png");
    pistolSprite.setOrigin(19, 19);
    bodyAnimation_.pistolSprite(pistolSprite, {24, 6});

    sf::Sprite rifleSprite = TextureManager::instance().loadSprite("data/guard/rifle.png");
    rifleSprite.setOrigin(19, 19);
    bodyAnimation_.rifleSprite(rifleSprite, {21, 9});

    sf::Sprite knifeSprite = TextureManager::instance().loadSprite("data/guard/knife.png");
    knifeSprite.setOrigin(19, 19);
    bodyAnimation_.knifeSprite(knifeSprite, {17, 0});
}

void Guard::startContact(GameObject* other) {
    if (dynamic_cast<Hideaway*>(other)) {
        usedHideaways++;
    }
}

void Guard::endContact(GameObject* other) {
    if (dynamic_cast<Hideaway*>(other)) {
        usedHideaways--;
    }
}