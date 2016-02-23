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


#ifndef SHOOTER_CHARACTER_H
#define SHOOTER_CHARACTER_H

#include <iostream>
#include "GameObject.h"
#include "TextureManager.h"
#include "Level.h"
#include "Wall.h"
#include "Item.h"
#include "LegAnimation.h"
#include "ItemList.h"
#include "BodyAnimation.h"
#include "LongEffect.h"


class Character : public GameObject {

    sf::Sprite sprite_;
    sf::Sprite headSprite_;

    const float friction = 99.1f;
    const float runSpeed = 850.0f;
    const float walkSpeed = 450.0f;

    float controlX = 0;
    float controlY = 0;

    Item items_[4] = {ItemList::get(ItemId::Knife),
                      ItemList::get(ItemId::AK47),
                      ItemList::get(ItemId::Glock),
                      ItemList::get(ItemId::Pistol9mmSilenced)};
    unsigned selectedItem_ = 0;

    int usedHideaways = 0;

    LegAnimation legAnimation_;
    double walkAngle = 0;

    BodyAnimation bodyAnimation_;

    void initBodyAnimation();

    b2Vec2 aimTarget;

    double alpha_ = 1;

public:
    Character(Level &level, float x, float y) : GameObject(&level), legAnimation_("data/player/legs.png", 14, 12) {
        sprite_ = TextureManager::instance().loadSprite("data/player/idle.png");
        sprite_.setOrigin(20, 20);

        headSprite_ = TextureManager::instance().loadSprite("data/player/helmet.png");
        headSprite_.setOrigin(9, 8);

        initBodyAnimation();

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

    virtual void render(PlayerViewport &viewport);

    void pulledTrigger();

    bool hidden() {
        return usedHideaways != 0;
    }

    virtual void startContact(GameObject* other);

    virtual void endContact(GameObject* other);

    virtual void update(Level &level, double deltaT);

    virtual void damage(const b2Vec2& hitPos) override {
        std::cout << "Player was hit" << std::endl;
        new LongEffect(level(), hitPos.x, hitPos.y);
    }

};


#endif //SHOOTER_CHARACTER_H
