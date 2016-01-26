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
#include "Ground.h"
#include "Weapon.h"


class Guard : public GameObject {

    sf::Sprite sprite_;
    sf::Sprite footSprite_;
    sf::Sprite suspicionSprite_;

    const float friction = 99.1f;
    const float speed = 850.0f;

    double suspicion = 0;

    Weapon weapon;

    b2Vec2 walkTarget;

public:
    Guard(Level &level, float x, float y) : GameObject(&level), weapon(&level) {
        sprite_ = TextureManager::instance().loadSprite("data/character.png");
        footSprite_ = TextureManager::instance().loadSprite("data/characterFoot.png");
        suspicionSprite_ = TextureManager::instance().loadSprite("data/suspicion.png");

        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x / SCALE, y / SCALE);
        BodyDef.type = b2_dynamicBody;
        BodyDef.linearDamping = 9;
        b2Body *Body = level.world().CreateBody(&BodyDef);
        Body->SetFixedRotation(true);

        b2CircleShape Shape;
        Shape.m_radius = 16/SCALE;
        b2FixtureDef FixtureDef;
        FixtureDef.density = 15.f;
        FixtureDef.friction = friction;
        FixtureDef.shape = &Shape;
        FixtureDef.userData = this;
        Body->CreateFixture(&FixtureDef);

        body(Body);
        level.add(this);

        walkTarget = b2Vec2(x / SCALE, y / SCALE);
    }

    void modSuspicion(double diff) {
        suspicion += diff;
        if (suspicion < 0)
            suspicion = 0;
        else if (suspicion > 1)
            suspicion = 1;
    }

    virtual void render(PlayerViewport &viewport) override {
        footSprite_.setOrigin(16, 26);
        footSprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
        footSprite_.setRotation(body()->GetAngle() * 180 / b2_pi);
        footSprite_.setScale((float) std::cos(level().time() * 10), 1);
        viewport.window().draw(footSprite_);

        sprite_.setOrigin(16, 26);
        sprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
        sprite_.setRotation(body()->GetAngle() * 180 / b2_pi);
        viewport.window().draw(sprite_);

        suspicionSprite_.setOrigin(16, 26);
        suspicionSprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y - 50);
        suspicionSprite_.setColor(sf::Color((sf::Uint8) (suspicion * 255), 0, 0, (sf::Uint8) (suspicion * 255)));
        viewport.window().draw(suspicionSprite_);
    }

    virtual void update(Level& level) override;
};


#endif //SHOOTER_GUARD_H
