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
#include "SoundManager.h"
#include <string>
#include <fstream>

std::uniform_real_distribution<double> Item::distribution(0, 100.0);

bool Item::tryUse(Level& level, b2Vec2 point, b2Vec2 targetPoint) {

    double angle = std::atan2(targetPoint.y - point.y, targetPoint.x - point.x);

    if (canUse(level)) {
        if (hasAmmunition_) {
            if (bulletsInMag_ > 0) {
                bulletsInMag_--;
            } else if (bullets_ > 0) {
                reload(level);
                return false;
            } else {
                nextFireTime = level.time() + 1;
                SoundManager::instance().playSound(emptySound_, point);
                return false;
            }
        }

        if (id_ == ItemId::Knife) {

            std::uniform_real_distribution<float> distribution(-0.3f, 0.3f);

            float xScale, yScale;

            xScale = 1 + distribution(Utils::rndGen);
            if (rand() % 2 == 0) {
                yScale = -1 + distribution(Utils::rndGen);
            } else {
                yScale = 1 + distribution(Utils::rndGen);
            }

            level.viewport().addEffect(level, EffectData("data/weapons/slash.png", -10, 26, angle).duration(0.1).scale(xScale, yScale).position(point));
        }

        std::normal_distribution<> d(0, precision_);

        angle += d(Utils::rndGen);

        double targetRange = Utils::length(targetPoint - point);

        if (targetRange > range_)
            targetRange = range_;

        targetPoint = {(float32) (point.x + std::cos(angle) * targetRange),
                       (float32) (point.y + std::sin(angle) * targetRange)};

        nextFireTime = level.time() + fireInterval_;
        showBurstUntil_ = level.time() + 0.05;

        Raycaster raycaster;
        raycaster.start = point;
        raycaster.passCoverChance_ = passCoverChance_;

        level.world().RayCast(&raycaster, point, targetPoint);

        if (raycaster.target) {
            GameObject* targetObject = (GameObject*) raycaster.target->GetUserData();

            targetObject->damage(raycaster.point);

            b2Vec2 impactImpulse(std::cos(angle) * 2, std::sin(angle) * 2);

            raycaster.target->GetBody()->ApplyLinearImpulse(impactImpulse, point, true);
        } else {
            if (class_ != ItemClass::Knife)
                createDust(level, targetPoint, angle);
        }
        SoundManager::instance().playSound(useSound_, point);

        return false;
    }
    return true;
}

void Item::createDust(Level& level, b2Vec2 point, float angle) {

    std::uniform_real_distribution<float> distribution(0, 10);
    std::normal_distribution<float> distributionPoint(0, 0.6);

    level.viewport().addEffect(level,
                               EffectData("data/effects/dust.png", distribution(Utils::rndGen))
                                       .position({point.x + distributionPoint(Utils::rndGen), point.y + distributionPoint(Utils::rndGen)})
                               .duration(1).fadesOut(true).scalesIn(true));
}

void Item::reload(Level& level) {
    fillMagazine();
    nextFireTime = level.time() + reloadTime_;
}