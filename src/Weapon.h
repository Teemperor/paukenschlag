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


#ifndef SHOOTER_WEAPON_H
#define SHOOTER_WEAPON_H


#include "Level.h"
#include "Utils.h"
#include <random>

class Weapon {

    Level* level_;
    double lastTimeFired = 0;
    double fireInterval = 0.1;
    double precision = 0.06;
    double passCoverChance = 8;

    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution;

    class Raycaster : public b2RayCastCallback {
    public:
        Weapon* weapon;

        b2Vec2 start;

        b2Vec2 point;
        b2Vec2 normal;
        b2Fixture* target = nullptr;
        double closestDistance = std::numeric_limits<double>::max();


        virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                      const b2Vec2& normal, float32 fraction) override {

            GameObject* object = static_cast<GameObject*>(fixture->GetUserData());

            if (object->hittable()) {
                double dist = Utils::distance(start, point);
                if (object->isCover()) {
                    if (dist < 2)
                        return -1;
                    else if (distribution(generator) < weapon->passCoverChance)
                        return -1;
                }
                if (dist < closestDistance) {
                    closestDistance = dist;
                    target = fixture;
                    this->point = point;
                    this->normal = normal;
                }
            }

            return -1;
        }
    };

public:
    Weapon(Level* level) : level_(level) {
    }

    bool canShoot() {
        return level_->time() > lastTimeFired + fireInterval;
    }

    bool tryShoot(b2Vec2 point, float angle) {
        if (canShoot()) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::normal_distribution<> d(0,precision);

            angle += d(gen);

            lastTimeFired = level_->time();

            b2Vec2 p2((float32) (cos(angle) * 15), (float32) (sin(angle) * 15));

            p2 += point;

            Raycaster raycaster;
            raycaster.start = point;
            raycaster.weapon = this;

            level_->world().RayCast(&raycaster, point, p2);

            if (raycaster.target) {
                GameObject* targetObject = (GameObject*) raycaster.target->GetUserData();

                targetObject->damage(raycaster.point);

                level_->viewport().addEffect(*level_, raycaster.point, angle);

                b2Vec2 impactImpulse(cos(angle) * 2, sin(angle) * 2);

                raycaster.target->GetBody()->ApplyLinearImpulse(impactImpulse, point, true);
            }

            return true;
        }
        return false;
    }
};


#endif //SHOOTER_WEAPON_H
