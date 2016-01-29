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


#include "Item.h"
#include "ItemList.h"
#include <string>
#include <fstream>

std::default_random_engine Item::generator;
std::uniform_real_distribution<double> Item::distribution(0, 100.0);

bool Item::tryUse(Level& level, b2Vec2 point, float angle) {



    if (canUse(level)) {
        if (hasAmmuniation_)
            bullets_--;

        if (id_ == ItemId::Knife) {
            sf::Sprite slashSprite = TextureManager::instance().loadSprite("data/weapons/slash.png");
            slashSprite.setOrigin(-10, slashSprite.getLocalBounds().height / 2);

            std::uniform_real_distribution<float> distribution(-0.3f, 0.3f);

            if (rand() % 2 == 0) {
                slashSprite.setScale(1 + distribution(generator), -1 + distribution(generator));
            } else {
                slashSprite.setScale(1 + distribution(generator), 1 + distribution(generator));
            }
            level.viewport().addEffect(level, point, angle, slashSprite);
        }


        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> d(0, precision_);

        angle += d(gen);

        lastTimeFired = level.time();

        b2Vec2 p2((float32) (cos(angle) * range_), (float32) (sin(angle) * range_));

        p2 += point;

        Raycaster raycaster;
        raycaster.start = point;
        raycaster.weapon = this;

        level.world().RayCast(&raycaster, point, p2);

        if (raycaster.target) {
            GameObject* targetObject = (GameObject*) raycaster.target->GetUserData();

            targetObject->damage(raycaster.point);

            sf::Sprite splashSprite = TextureManager::instance().loadSprite("data/effects/splash.png");
            splashSprite.setOrigin(splashSprite.getLocalBounds().width / 2, splashSprite.getLocalBounds().height / 2);
            level.viewport().addEffect(level, raycaster.point, angle, splashSprite);

            b2Vec2 impactImpulse(cos(angle) * 2, sin(angle) * 2);

            raycaster.target->GetBody()->ApplyLinearImpulse(impactImpulse, point, true);
        }

        return true;
    }
    return false;
}