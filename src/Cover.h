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


#ifndef SHOOTER_COVER_H
#define SHOOTER_COVER_H


#include "GameObject.h"
#include "TextureManager.h"
#include "Level.h"

class Cover  : public GameObject {

    sf::Sprite sprite_;

public:
    Cover(Level& level, float x, float y) : GameObject(&level) {
        sprite_ = TextureManager::instance().loadSprite("data/cover/sandbags.png");

        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x/SCALE, y/SCALE);
        BodyDef.angle = 0.1f;
        BodyDef.type = b2_staticBody;
        b2Body* Body = level.world().CreateBody(&BodyDef);

        b2PolygonShape Shape;
        Shape.SetAsBox((107.f/2)/SCALE, (40.f/2)/SCALE);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 0.f;
        FixtureDef.shape = &Shape;
        FixtureDef.userData = this;
        Body->CreateFixture(&FixtureDef);

        body(Body);
        level.add(this);
    }

    virtual void render(PlayerViewport& viewport) override {
        sprite_.setOrigin(107/2, 40/2);
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

#endif //SHOOTER_COVER_H
