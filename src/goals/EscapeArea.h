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


#ifndef SHOOTER_ESCAPEAREA_H
#define SHOOTER_ESCAPEAREA_H

#include "GameObject.h"
#include <iostream>
#include "GameObject.h"
#include "TextureManager.h"
#include "Level.h"
#include "Wall.h"
#include "Item.h"

class EscapeArea : public GameObject {

    sf::Sprite sprite_;

public:
    EscapeArea(Level &level, float x, float y) : GameObject(&level) {
            sprite_ = TextureManager::instance().loadSprite("data/effects/escape.png");
            sprite_.setOrigin(40, 40);

            b2BodyDef BodyDef;
            BodyDef.position = b2Vec2(x / SCALE, y / SCALE);
            BodyDef.type = b2_staticBody;
            BodyDef.linearDamping = 9;
            b2Body *Body = level.world().CreateBody(&BodyDef);
            Body->SetFixedRotation(true);

            b2CircleShape Shape;
            Shape.m_radius = 10 / SCALE;
            b2FixtureDef FixtureDef;
            FixtureDef.shape = &Shape;
            FixtureDef.userData = this;
            FixtureDef.isSensor = true;
            Body->CreateFixture(&FixtureDef);

            body(Body);
            level.add(this);
    }

    virtual bool hittable() const {
        return false;
    }

    virtual void render(PlayerViewport &viewport) override {
        float scale = (((unsigned) (1000 * viewport.level().time() * 2)) % 2000) / 1000.0f;
        sprite_.setScale(scale, scale);
        sprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
        float opacity = (2 - scale) / 2;
        sprite_.setColor(sf::Color(255, 255, 255, (sf::Uint8) (255 * opacity)));
        sprite_.setRotation(body()->GetAngle() * 180 / b2_pi);
        viewport.window().draw(sprite_);

    }

    virtual void update(Level& level, double deltaT) override {
    }


    virtual void startContact(GameObject* other) override {
    }

    virtual void endContact(GameObject* other) override {
    }

};
#endif //SHOOTER_ESCAPEAREA_H
