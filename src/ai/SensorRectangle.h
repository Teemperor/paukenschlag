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


#ifndef SHOOTER_SENSORRECTANGLE_H
#define SHOOTER_SENSORRECTANGLE_H

#include <iostream>
#include "GameObject.h"
#include "TextureManager.h"
#include "Level.h"
#include "Wall.h"
#include "Item.h"


class SensorRectangle : public GameObject {

    bool hasContact_ = false;

public:
    SensorRectangle(Level &level, float x, float y, float w, float h) : GameObject(&level) {
        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(x, y);
        BodyDef.type = b2_staticBody;
        BodyDef.linearDamping = 9;
        b2Body *Body = level.world().CreateBody(&BodyDef);
        Body->SetFixedRotation(true);

        b2PolygonShape Shape;
        Shape.SetAsBox(w, h);
        b2FixtureDef FixtureDef;
        FixtureDef.shape = &Shape;
        FixtureDef.userData = this;
        FixtureDef.isSensor = true;
        Body->CreateFixture(&FixtureDef);

        body(Body);

        level.world().Step(0, 8, 3);
    }

    virtual bool hittable() const override {
        return false;
    }

    virtual void render(PlayerViewport &viewport) override {
    }

    virtual void update(Level& level, double deltaT) override {
    }


    virtual void startContact(GameObject* other) override;

    virtual void endContact(GameObject* other) override;

    virtual bool transparent() const override {
        return true;
    }
};


#endif //SHOOTER_SENSORRECTANGLE_H
