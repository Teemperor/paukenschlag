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

class ItemList;

enum class ItemId {
    None,
    AK47,
    Knife,
    M14,
    Pistol9mmSilenced,
};

class Item {

    friend class ItemList;

    ItemId id_;

    std::string name_;

    sf::Sprite icon_;
    double range_ = 15;
    double lastTimeFired = 0;
    double fireInterval_ = 0.1;
    double precision_ = 0.06;
    double passCoverChance_ = 8;
    unsigned bullets_ = 1;
    unsigned maxBullets_ = 1;
    bool hasAmmuniation_ = false;

    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution;


    class Raycaster : public b2RayCastCallback {
    public:
        Item * weapon;

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
                    else if (distribution(generator) < weapon->passCoverChance_)
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
    Item() {
    }

    bool canUse(Level &level) {
        if (hasAmmuniation_ && bullets_ == 0)
            return false;
        return level.time() > lastTimeFired + fireInterval_;
    }

    bool tryUse(Level& level, b2Vec2 point, float angle);

    sf::Sprite& icon() {
        return icon_;
    }

    Item& icon(const std::string& path) {
        icon_ = TextureManager::instance().loadSprite(path);
        icon_.setOrigin(icon_.getLocalBounds().width / 2, icon_.getLocalBounds().height / 2);

        float diameter = std::sqrt(icon_.getLocalBounds().width * icon_.getLocalBounds().width + icon_.getLocalBounds().height * icon_.getLocalBounds().height);

        icon_.setScale(57 / diameter, 57 / diameter);
        return *this;
    }

    Item& name(const std::string& name) {
        name_ = name;
        return *this;
    }

    Item& fireInterval(double interval) {
        fireInterval_ = interval;
        return *this;
    }
    Item& precision(double value) {
        precision_ = value;
        return *this;
    }
    Item& passCoverChance(double value) {
        passCoverChance_ = value;
        return *this;
    }

    Item& id(ItemId id) {
        id_ = id;
        return *this;
    }

    Item& range(double range) {
        range_ = range;
        return *this;
    }

    Item& bullets(unsigned bullets) {
        bullets_ = maxBullets_ = bullets;
        hasAmmuniation_ = true;
        return *this;
    }
};


#endif //SHOOTER_WEAPON_H