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
#include "Utils.h"

class LongEffect : public GameObject {

    sf::Sprite sprite_;
    double scale_ = 0;

public:
    LongEffect(Level& level, double x, double y) : GameObject(&level) {
            sprite_ = TextureManager::instance().loadSprite("data/effects/blood1.png");
            sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);

            b2BodyDef BodyDef;
            BodyDef.position = b2Vec2( x, y);
            BodyDef.type = b2_dynamicBody;
            BodyDef.linearDamping = 10;
            BodyDef.angularDamping = 10;
            b2Body* Body = level.world().CreateBody(&BodyDef);

            b2PolygonShape Shape;
            Shape.SetAsBox(1, 1);
            b2FixtureDef FixtureDef;
            FixtureDef.filter.categoryBits = 0;
            FixtureDef.filter.maskBits = 0;
            FixtureDef.density = 64.f;
            FixtureDef.friction = 0.9f;
            FixtureDef.shape = &Shape;
            FixtureDef.userData = this;
            Body->CreateFixture(&FixtureDef);

            body(Body);
            level.add(this);
    }

    virtual void render(PlayerViewport& viewport) override {
        sprite_.setScale((float) scale_, (float) scale_);
        sprite_.setColor(sf::Color(255, 255, 255, (sf::Uint8) (scale_ * 255)));
        sprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
        sprite_.setRotation(body()->GetAngle() * 180/b2_pi);
        viewport.window().draw(sprite_);
    }

    virtual void update(Level& level, double deltaT) override {
        Utils::animateTo(scale_, 1, deltaT, 1);
    }

    virtual bool isCover() const override {
        return false;
    }

    virtual bool hittable() const {
        return false;
    }

    virtual bool transparent() const override {
        return true;
    }
};


#endif //SHOOTER_LONGEFFECT_H
