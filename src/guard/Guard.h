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


#ifndef SHOOTER_GUARD_H
#define SHOOTER_GUARD_H

#include <iostream>
#include <LegAnimation.h>
#include <LongEffect.h>
#include "GameObject.h"
#include "TextureManager.h"
#include "Level.h"
#include "Wall.h"
#include "Item.h"
#include "SuspicionIndicator.h"
#include "GuardAI.h"
#include "FOVIndicator.h"


class Guard : public GameObject {

    friend class GuardAI;

    sf::Sprite deadSprite_;
    sf::Sprite sprite_;
    sf::Sprite headSprite_;

    const float friction = 99.1f;
    const float walkSpeed = 350.0f;
    const float runSpeed = 850.0f;

    Item weapon_;

    float headRotation = 0;
    float headRotationTarget = 0;

    SuspicionIndicator suspicionIndicator_;

    GuardAI ai_;

    bool dead_ = false;

    LegAnimation legAnimation;
    BodyAnimation bodyAnimation_;

    FOVIndicator fovIndicator;

    void initBodyAnimation();

public:
    Guard(Level &level, float x, float y) : GameObject(&level), legAnimation("data/guard/legs.png", 14, 12) {
        sprite_ = TextureManager::instance().loadSprite("data/guard/idle.png");
        sprite_.setOrigin(20, 20);

        if (Utils::rndGen() % 100 < 30) {
            weapon_ = ItemList::get(ItemId::AK47);
        } else {
            weapon_ = ItemList::get(ItemId::Glock);
        }

        headSprite_ = TextureManager::instance().loadSprite("data/guard/helmet.png");
        headSprite_.setOrigin(9, 8);

        deadSprite_ = TextureManager::instance().loadSprite("data/guard/dead.png");
        deadSprite_.setOrigin(40, 45);

        initBodyAnimation();

        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x / SCALE, y / SCALE);
        BodyDef.type = b2_dynamicBody;
        BodyDef.linearDamping = 9;
        b2Body *Body = level.world().CreateBody(&BodyDef);
        Body->SetFixedRotation(true);

        b2CircleShape Shape;
        Shape.m_radius = 16 / SCALE;
        b2FixtureDef FixtureDef;
        FixtureDef.density = 15.f;
        FixtureDef.filter.categoryBits = 0x2;
        FixtureDef.filter.maskBits = ~0x2;
        FixtureDef.friction = friction;
        FixtureDef.shape = &Shape;
        FixtureDef.userData = this;
        Body->CreateFixture(&FixtureDef);

        body(Body);
        level.add(this);
    }


    virtual void render(PlayerViewport &viewport) override {
        if (dead_) {
            deadSprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
            deadSprite_.setRotation(body()->GetAngle() * 180 / b2_pi);
            viewport.window().draw(deadSprite_);
        } else {
            fovIndicator.render(viewport, position(), getViewDirection(), ai_.fieldOfView(), ai_.suspicion());

            legAnimation.render(position(), body()->GetAngle(), viewport);

            bodyAnimation_.draw(weapon_, viewport, position(), body()->GetAngle());

            headSprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
            headSprite_.setRotation((body()->GetAngle() + headRotation) * 180 / b2_pi);
            viewport.window().draw(headSprite_);

            //suspicionIndicator_.draw(viewport, SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y - 40, ai_.suspicion());
        }
    }



    void rotateTo(const b2Vec2& target) {
        body()->SetTransform(body()->GetPosition(),
                             (float32) std::atan2(target.y - body()->GetPosition().y, target.x - body()->GetPosition().x));
    }

    void walkForward() {
        legAnimation.state(LegAnimation::State::Walking);
        body()->ApplyForce(b2Vec2((float32) (std::cos(body()->GetAngle()) * walkSpeed),
                                  (float32) (std::cos(body()->GetAngle() - M_PI / 2) * walkSpeed)),
                           body()->GetWorldCenter(), true);
    }

    void runForward() {
        legAnimation.state(LegAnimation::State::Running);
        body()->ApplyForce(b2Vec2((float32) (std::cos(body()->GetAngle()) * runSpeed),
                                  (float32) (std::cos(body()->GetAngle() - M_PI / 2) * runSpeed)),
                           body()->GetWorldCenter(), true);

    }

    void stopWalking() {
        legAnimation.state(LegAnimation::State::Standing);
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

    Item & weapon() {
        return weapon_;
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
