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


#ifndef SHOOTER_EFFECTDATA_H
#define SHOOTER_EFFECTDATA_H

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <Box2D/Common/b2Math.h>
#include "TextureManager.h"
#include "Constants.h"

class EffectData {

    bool fadesIn_ = false;
    bool fadesOut_ = false;
    bool scalesIn_ = false;
    float rotationSpeed_ = 0;
    double duration_ = 0.1;
    sf::Sprite sprite_;
    b2Vec2 position_;

public:
    EffectData(const std::string& path, float ox, float oy, double rotation) {
        sprite_ = TextureManager::instance().loadSprite(path);
        sprite_.setOrigin(ox, oy);
        sprite_.setRotation((float) (rotation * 180 / b2_pi));
    }
    EffectData(const std::string& path, double rotation) {
        sprite_ = TextureManager::instance().loadSprite(path);
        sprite_.setOrigin(sprite_.getLocalBounds().width / 2, sprite_.getLocalBounds().height / 2);
        sprite_.setRotation((float) (rotation * 180 / b2_pi));
    }

    bool fadesIn() {
        return fadesIn_;
    }

    bool fadesOut() {
        return fadesOut_;
    }

    bool scalesIn() {
        return scalesIn_;
    }

    double duration() {
        return duration_;
    }

    float rotationSpeed() {
        return rotationSpeed_;
    }

    sf::Sprite& sprite() {
        return sprite_;
    }

    b2Vec2& position() {
        return position_;
    }

    EffectData& scale(float x, float y) {
        sprite_.setScale(x, y);
        return *this;
    }

    EffectData& position(const b2Vec2& pos) {
        sprite_.setPosition(pos.x * SCALE, pos.y * SCALE);
        position_ = pos;
        return *this;
    }

    EffectData& fadesIn(bool value) {
        fadesIn_ = value;
        return *this;
    }

    EffectData& fadesOut(bool value) {
        fadesOut_ = value;
        return *this;
    }

    EffectData& duration(double duration) {
        duration_ = duration;
        return *this;
    }

    EffectData& rotationSpeed(float rotationSpeed) {
        rotationSpeed_ = rotationSpeed;
        return *this;
    }

    EffectData& scalesIn(bool value) {
        scalesIn_ = value;
        return *this;
    }

};


#endif //SHOOTER_EFFECTDATA_H
