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


#ifndef SHOOTER_SOLDIER_H
#define SHOOTER_SOLDIER_H

#include <iostream>
#include <LegAnimation.h>
#include <LongEffect.h>
#include <BodyAnimation.h>
#include <ItemList.h>
#include "GameObject.h"
#include "TextureManager.h"
#include "Level.h"
#include "Wall.h"
#include "Item.h"
#include "SuspicionIndicator.h"
#include "GuardAI.h"
#include "FOVIndicator.h"


class Soldier : public GameObject {

    friend class GuardAI;

    sf::Sprite deadSprite_;
    sf::Sprite sprite_;
    sf::Sprite headSprite_;

    const float friction = 99.1f;
    const float walkSpeed = 350.0f;
    const float runSpeed = 850.0f;

    float headRotation = 0;
    float headRotationTarget = 0;

    SuspicionIndicator suspicionIndicator_;

    GuardAI ai_;

    bool dead_ = false;

    LegAnimation legAnimation_;
    BodyAnimation bodyAnimation_;

    FOVIndicator fovIndicator;

    bool visible_ = false;

    double alpha_ = 0;

    void initBodyAnimation();

    int usedHideaways = 0;

    bool isPlayer_ = false;

    b2Vec2 aimTarget;
    double walkAngle = 0;
    Item items_[4] = {ItemList::get(ItemId::Knife),
                      ItemList::get(ItemId::AK47),
                      ItemList::get(ItemId::Glock),
                      ItemList::get(ItemId::Pistol9mmSilenced)};
    unsigned selectedItem_ = rand() % 2 + 1;
    float controlX = 0;
    float controlY = 0;


public:
    Soldier(Level &level, float x, float y);

    virtual void startContact(GameObject* other) override;

    virtual void endContact(GameObject* other) override;

    virtual void render(PlayerViewport &viewport) override;

    void setIsPlayer(bool isPlayer);

    bool isPlayer() const {
        return isPlayer_;
    }

    Item& currentItem() {
        return items_[selectedItem_];
    }

    Item* items() {
        return items_;
    }

    unsigned selectedItemIndex() {
        return selectedItem_;
    }

    bool hidden() {
        return usedHideaways != 0;
    }

    void pullTrigger() {
        currentItem().tryUse(level(), body()->GetPosition(), aimTarget);
    }

    void rotateTo(const b2Vec2& target) {
        body()->SetTransform(body()->GetPosition(),
                             (float32) std::atan2(target.y - body()->GetPosition().y, target.x - body()->GetPosition().x));
    }

    void walkForward() {
        legAnimation_.state(LegAnimation::State::Walking);
        body()->ApplyForce(b2Vec2((float32) (std::cos(body()->GetAngle()) * walkSpeed),
                                  (float32) (std::cos(body()->GetAngle() - M_PI / 2) * walkSpeed)),
                           body()->GetWorldCenter(), true);
    }

    void runForward() {
        legAnimation_.state(LegAnimation::State::Running);
        body()->ApplyForce(b2Vec2((float32) (std::cos(body()->GetAngle()) * runSpeed),
                                  (float32) (std::cos(body()->GetAngle() - M_PI / 2) * runSpeed)),
                           body()->GetWorldCenter(), true);

    }

    void stopWalking() {
        legAnimation_.state(LegAnimation::State::Standing);
    }

    GuardAI& ai() {
        return ai_;
    }

    virtual void update(Level& level, double deltaT) override;

    void setHeadRotation(float newTargetRotation) {
        headRotationTarget = newTargetRotation;
    }

    void shoot(b2Vec2 target);

    virtual void damage(const b2Vec2& hitPos) override {
        if (!dead_)
            new LongEffect(level(), hitPos.x, hitPos.y);

        dead_ = true;
        b2Filter filter;
        filter.groupIndex = 0;
        filter.maskBits = 0;
        body()->GetFixtureList()->SetFilterData(filter);

    }

    float getViewDirection() {
        return body()->GetAngle() + headRotation;
    }

    bool dead() const {
        return dead_;
    }

    virtual bool hittable() const override {
        return !dead_;
    }

    virtual bool transparent() const override {
        return true;
    }
};


#endif //SHOOTER_GUARD_H
