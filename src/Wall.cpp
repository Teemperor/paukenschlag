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


#include "Wall.h"

void Wall::render(PlayerViewport& viewport) {

        float startX = start_.x;
        float startY = start_.y;

        int parts = (int) length_;

        for (int i = 1; i < parts - 1; i++) {
                sprite_.setPosition((startX + std::cos(angle_) * i) * SCALE, (startY + std::sin(angle_) * i) * SCALE);
                sprite_.setRotation(angle_ * 180 / b2_pi);
                viewport.window().draw(sprite_);
        }

        spriteStart_.setPosition(startX * SCALE, startY * SCALE);
        spriteStart_.setRotation(angle_ * 180 / b2_pi);
        viewport.window().draw(spriteStart_);

        float endX = startX + (length_ - 1) * std::cos(angle_);
        float endY = startY + (length_ - 1) * std::sin(angle_);

        spriteEnd_.setPosition(endX * SCALE, endY * SCALE);
        spriteEnd_.setRotation(angle_ * 180 / b2_pi);
        viewport.window().draw(spriteEnd_);
}

Wall::Wall(Level& level, const b2Vec2& start, const b2Vec2& end, const std::string& filePath)
        : GameObject(&level), start_(start) {
        b2Vec2 mid = b2Vec2((start.x + end.x) / 2, (start.y + end.y) / 2);
        length_ = Utils::distance(start, end);
        b2Vec2 delta = end - start;
        angle_ = std::atan2(delta.y, delta.x);

        sprite_ = TextureManager::instance().loadSprite(filePath + ".png");
        sprite_.setOrigin(0, sprite_.getLocalBounds().height / 2);

        spriteStart_ = TextureManager::instance().loadSprite(filePath + "Start.png");
        spriteStart_.setOrigin(0, spriteStart_.getLocalBounds().height / 2);

        spriteEnd_ = TextureManager::instance().loadSprite(filePath + "End.png");
        spriteEnd_.setOrigin(0, spriteEnd_.getLocalBounds().height / 2);

        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2(mid.x, mid.y);
        BodyDef.angle = angle_;
        BodyDef.type = b2_staticBody;
        b2Body* Body = level.world().CreateBody(&BodyDef);

        b2PolygonShape Shape;
        Shape.SetAsBox(length_ / 2, halfWallWidth);
        b2FixtureDef FixtureDef;
        FixtureDef.density = 0.f;
        FixtureDef.shape = &Shape;
        FixtureDef.userData = this;
        FixtureDef.friction = 0;
        FixtureDef.filter.categoryBits = objectCategory::WALL;
        FixtureDef.filter.maskBits = ~objectCategory::WALL;

        Body->CreateFixture(&FixtureDef);

        body(Body);
        level.add(this);
}