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
    Glock,
    Pistol9mmSilenced,
};

enum class ItemClass {
    None,
    Knife,
    Pistol,
    Rifle
};

class Item {

    friend class ItemList;

    ItemId id_;
    ItemClass class_;

    std::string name_;

    std::string useSound_;
    std::string emptySound_;

    sf::Sprite crossHair_;
    sf::Sprite sprite_;
    sf::Sprite burstSprite_;
    sf::Sprite icon_;
    double range_ = 15;
    double nextFireTime = 0;
    double fireInterval_ = 0.1;
    double precision_ = 0.06;
    double passCoverChance_ = 8;
    unsigned bulletsInMag_ = 0;
    unsigned magSize_ = 1;
    unsigned bullets_ = 1;
    unsigned maxBullets_ = 1;
    double reloadTime_ = 1;
    bool hasAmmunition_ = false;
    bool automatic_ = false;

    double showBurstUntil_ = 0;

    static std::uniform_real_distribution<double> distribution;


    void createDust(Level& level, b2Vec2 point, float angle);

    void fillMagazine() {
        while (bullets_ > 0 && bulletsInMag_ < magSize_) {
            bullets_--;
            bulletsInMag_++;
        }
    }
public:
    Item() {
    }

    class Raycaster : public b2RayCastCallback {
    public:
        double passCoverChance_ = 0;

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
                    else if (distribution(Utils::rndGen) < passCoverChance_)
                        return -1;
                }
                if (dist < closestDistance) {
                    closestDistance = dist;
                    target = fixture;
                    this->point = point;
                    this->normal = normal;
                }
            }

            return 1;
        }
    };


    bool showBurst(double time) const {
        return time < showBurstUntil_;
    }

    bool canUse(Level &level) {
        return level.time() > nextFireTime;
    }

    void reload(Level& level);

    bool tryUse(Level& level, b2Vec2 point, b2Vec2 targetPoint);

    sf::Sprite& icon() {
        return icon_;
    }

    sf::Sprite& sprite() {
        return sprite_;
    }

    sf::Sprite& burstSprite() {
        return burstSprite_;
    }

    sf::Sprite& crosshair() {
        return crossHair_;
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

    ItemClass& itemClass() {
        return class_;
    }

    bool isAutomatic() {
        return automatic_;
    }

    Item& useSound(const std::string& filePath) {
        useSound_ = filePath;
        return *this;
    }

    Item& emptySound(const std::string& filePath) {
        emptySound_ = filePath;
        return *this;
    }

    Item& sprite(const std::string& path, float ox, float oy) {
        sprite_ = TextureManager::instance().loadSprite(path);
        sprite_.setOrigin(ox, oy);
        return *this;
    }

    Item& crosshair(const std::string& path) {
        crossHair_ = TextureManager::instance().loadSprite(path);
        crossHair_.setOrigin(crossHair_.getLocalBounds().width / 2, crossHair_.getLocalBounds().height / 2);
        return *this;
    }

    Item& burstSprite(const std::string& path, float ox, float oy) {
        burstSprite_ = TextureManager::instance().loadSprite(path);
        burstSprite_.setOrigin(ox, oy);
        return *this;
    }

    Item& itemClass(ItemClass itemClass) {
        class_ = itemClass;
        return *this;
    }

    Item& id(ItemId id) {
        id_ = id;
        return *this;
    }

    Item& automatic(bool automatic) {
        automatic_ = automatic;
        return *this;
    }

    Item& range(double range) {
        range_ = range;
        return *this;
    }

    Item& bullets(unsigned magSize, unsigned bullets, double reloadTime) {
        magSize_ = magSize;
        bullets_ = maxBullets_ = bullets;
        reloadTime_ = reloadTime;
        hasAmmunition_ = true;
        fillMagazine();
        return *this;
    }
};


#endif //SHOOTER_WEAPON_H
