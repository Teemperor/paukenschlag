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


#ifndef SHOOTER_BODYANIMATION_H
#define SHOOTER_BODYANIMATION_H


#include <SFML/Graphics/Sprite.hpp>
#include <Box2D/Common/b2Math.h>
#include "Constants.h"
#include "PlayerViewport.h"
#include "Item.h"

class BodyAnimation {

    sf::Sprite idleSprite_;
    sf::Sprite knifeSprite_;
    b2Vec2 knifePos_;
    sf::Sprite pistolSprite_;
    b2Vec2 pistolPos_;
    sf::Sprite rifleSprite_;
    b2Vec2 riflePos_;

    void drawItem(Item& currentItem, PlayerViewport &viewport, const b2Vec2& position, double angle, b2Vec2 itemOffset) {
        itemOffset.x /= SCALE;
        itemOffset.y /= SCALE;
        b2Vec2 itemPosition = {(float32) (position.x + std::cos(angle) * itemOffset.x - std::sin(angle) * itemOffset.y),
                               (float32) (position.y + std::sin(angle) * itemOffset.x + std::cos(angle) * itemOffset.y)};
        currentItem.sprite().setPosition(itemPosition.x * SCALE, itemPosition.y * SCALE);
        currentItem.sprite().setRotation((float) (angle * 180 / b2_pi));
        viewport.window().draw(currentItem.sprite());
    }

public:
    BodyAnimation() {
    }

    void idleSprite(const sf::Sprite& sprite) {
        idleSprite_ = sprite;
    }

    void knifeSprite(const sf::Sprite& sprite, const b2Vec2& pos) {
        knifeSprite_ = sprite;
        knifePos_ = pos;
    }

    void pistolSprite(const sf::Sprite& sprite, const b2Vec2& pos) {
        pistolSprite_ = sprite;
        pistolPos_ = pos;
    }

    void rifleSprite(const sf::Sprite& sprite, const b2Vec2& pos) {
        rifleSprite_ = sprite;
        riflePos_ = pos;
    }

    void draw(Item& currentItem, PlayerViewport &viewport, const b2Vec2& position, double angle) {
        float angleInDegrees = (float) (angle * 180 / b2_pi);
        switch(currentItem.itemClass()) {
            case ItemClass::None:
                idleSprite_.setPosition(position.x * SCALE, position.y * SCALE);
                idleSprite_.setRotation(angleInDegrees);
                viewport.window().draw(idleSprite_);
                break;
            case ItemClass::Knife:
                knifeSprite_.setPosition(position.x * SCALE, position.y * SCALE);
                knifeSprite_.setRotation(angleInDegrees);
                viewport.window().draw(knifeSprite_);
                drawItem(currentItem, viewport, position, angle, knifePos_);
                break;
            case ItemClass::Pistol:
                pistolSprite_.setPosition(position.x * SCALE, position.y * SCALE);
                pistolSprite_.setRotation(angleInDegrees);
                viewport.window().draw(pistolSprite_);
                drawItem(currentItem, viewport, position, angle, pistolPos_);
                break;
            case ItemClass::Rifle:
                rifleSprite_.setPosition(position.x * SCALE, position.y * SCALE);
                rifleSprite_.setRotation(angleInDegrees);
                viewport.window().draw(rifleSprite_);
                drawItem(currentItem, viewport, position, angle, riflePos_);
                break;
            default:
                assert(false);
        }
    }

};


#endif //SHOOTER_BODYANIMATION_H
