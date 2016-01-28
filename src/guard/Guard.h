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
#include "GameObject.h"
#include "TextureManager.h"
#include "Level.h"
#include "Wall.h"
#include "Weapon.h"
#include "SuspicionIndicator.h"
#include "GuardAI.h"


class Guard : public GameObject {

    friend class GuardAI;

    sf::Sprite deadSprite_;
    sf::Sprite sprite_;
    sf::Sprite footSprite_;
    sf::Sprite headSprite_;

    const float friction = 99.1f;
    const float speed = 850.0f;

    Weapon weapon_;

    float headRotation = 0;
    float headRotationTarget = 0;

    SuspicionIndicator suspicionIndicator_;

    GuardAI ai_;

    bool dead_ = false;

public:
    Guard(Level &level, float x, float y) : GameObject(&level), weapon_(&level) {
        sprite_ = TextureManager::instance().loadSprite("data/guard/idle.png");
        sprite_.setOrigin(20, 20);

        footSprite_ = TextureManager::instance().loadSprite("data/guard/legs.png");
        footSprite_.setOrigin(14, 12);

        headSprite_ = TextureManager::instance().loadSprite("data/guard/helmet.png");
        headSprite_.setOrigin(9, 8);

        deadSprite_ = TextureManager::instance().loadSprite("data/guard/dead.png");
        deadSprite_.setOrigin(40, 45);

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
            footSprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
            footSprite_.setRotation(body()->GetAngle() * 180 / b2_pi);
            footSprite_.setScale((float) std::cos(level().time() * 5) * 1.2f, 1);
            viewport.window().draw(footSprite_);

            sprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
            sprite_.setRotation(body()->GetAngle() * 180 / b2_pi);
            viewport.window().draw(sprite_);

            headSprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
            headSprite_.setRotation((body()->GetAngle() + headRotation) * 180 / b2_pi);
            viewport.window().draw(headSprite_);

            suspicionIndicator_.draw(viewport, SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y - 40, ai_.suspicioun());
        }
    }

    virtual void update(Level& level, double deltaT) override;

    void setHeadRotation(float newTargetRotation) {
        headRotationTarget = newTargetRotation;
    }

    virtual void damage(const b2Vec2& hitPos) override {
        dead_ = true;
        b2Filter filter;
        filter.groupIndex = 0;
        filter.maskBits = 0;
        body()->GetFixtureList()->SetFilterData(filter);
    }

    float getViewDirection() {
        return body()->GetAngle() + headRotation;
    }

    Weapon& weapon() {
        return weapon_;
    }

    bool dead() const {
        return dead_;
    }
};


#endif //SHOOTER_GUARD_H
