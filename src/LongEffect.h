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


#ifndef SHOOTER_LONGEFFECT_H
#define SHOOTER_LONGEFFECT_H


#include "GameObject.h"
#include "Level.h"

class LongEffect : public GameObject {

    sf::Sprite sprite_;

public:
    LongEffect(Level& level, float x, float y) : GameObject(&level) {
            sprite_ = TextureManager::instance().loadSprite("data/crates/box.png");

            b2BodyDef BodyDef;
            BodyDef.position = b2Vec2(x/SCALE, y/SCALE);
            BodyDef.type = b2_dynamicBody;
            BodyDef.linearDamping = 10;
            BodyDef.angularDamping = 10;
            b2Body* Body = level.world().CreateBody(&BodyDef);

            b2PolygonShape Shape;
            Shape.SetAsBox((32.f/2)/SCALE, (32.f/2)/SCALE);
            b2FixtureDef FixtureDef;
            FixtureDef.density = 64.f;
            FixtureDef.friction = 0.9f;
            FixtureDef.shape = &Shape;
            FixtureDef.userData = this;
            Body->CreateFixture(&FixtureDef);

            body(Body);
            level.add(this);

    }

    virtual void render(PlayerViewport& viewport) override {
        sprite_.setOrigin(16.f, 16.f);
        sprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
        sprite_.setRotation(body()->GetAngle() * 180/b2_pi);
        viewport.window().draw(sprite_);
    }

    virtual void update(Level& level, double deltaT) override {
    }

    virtual bool isCover() const override {
        return true;
    }
};


#endif //SHOOTER_LONGEFFECT_H
