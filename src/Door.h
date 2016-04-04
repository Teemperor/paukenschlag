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


#ifndef SHOOTER_DOOR_H
#define SHOOTER_DOOR_H

#include "GameObject.h"
#include "TextureManager.h"
#include "Level.h"

class Door : public GameObject {

    sf::Sprite sprite_;

public:
    Door(Level& level, float x, float y) : GameObject(&level) {
            sprite_ = TextureManager::instance().loadSprite("data/doors/door.png");

        b2BodyDef JointBodyDef;
        JointBodyDef.position = b2Vec2(x / SCALE, y / SCALE);
        JointBodyDef.type = b2_staticBody;
        b2Body* JointBody = level.world().CreateBody(&JointBodyDef);

        b2PolygonShape JointShape;
        JointShape.SetAsBox(0.001, 0.001);
        b2FixtureDef JointFixtureDef;
        JointFixtureDef.density = 64.f;
        JointFixtureDef.friction = 0.9f;
        JointFixtureDef.shape = &JointShape;
        JointFixtureDef.userData = this;
        JointBody->CreateFixture(&JointFixtureDef);

        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2((x + 32) / SCALE, y / SCALE);
        BodyDef.type = b2_dynamicBody;
        BodyDef.linearDamping = 1;
        BodyDef.angularDamping = 5;
        b2Body* Body = level.world().CreateBody(&BodyDef);

        b2PolygonShape Shape;
        Shape.SetAsBox(32.f / SCALE, 3.f / SCALE);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 64.f;
        FixtureDef.friction = 0.0f;
        FixtureDef.shape = &Shape;
        FixtureDef.filter.categoryBits = objectCategory::THING;
        FixtureDef.filter.maskBits = ~objectCategory::WALL;
        FixtureDef.userData = this;

        Body->CreateFixture(&FixtureDef);

        b2RevoluteJointDef revoluteJointDef;
        revoluteJointDef.bodyA = Body;
        revoluteJointDef.bodyB = JointBody;
        revoluteJointDef.collideConnected = false;
        revoluteJointDef.localAnchorA.Set(-32 / SCALE, 3 / SCALE);
        revoluteJointDef.localAnchorB.Set(0, 0);
        revoluteJointDef.lowerAngle = -b2_pi * 0.6f;
        revoluteJointDef.upperAngle = b2_pi * 0.6f;
        revoluteJointDef.enableLimit = true;
        b2Joint* joint = level.world().CreateJoint(&revoluteJointDef);

        body(Body);
        level.add(this);

    }

    virtual void render(PlayerViewport& viewport) override {
        sprite_.setOrigin(32, 3.f);
        sprite_.setPosition(SCALE * body()->GetPosition().x, SCALE * body()->GetPosition().y);
        sprite_.setRotation(body()->GetAngle() * 180 / b2_pi);
        viewport.window().draw(sprite_);
    }

    virtual bool blocksView() const override{
        return true;
    }

    virtual void update(Level& level, double deltaT) override {
    }

    virtual bool isCover() const override {
        return false;
    }

    virtual bool transparent() const override {
        return false;
    }
};


#endif //SHOOTER_DOOR_H
