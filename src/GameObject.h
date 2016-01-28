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


#ifndef SHOOTER_GAMEOBJECT_H
#define SHOOTER_GAMEOBJECT_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "PlayerViewport.h"
#include "Constants.h"

class Level;

class GameObject {

    b2Body* body_ = nullptr;
    Level* level_ = nullptr;

public:
    GameObject() {
    }
    GameObject(Level* level) : level_(level) {

    }

    virtual void render(PlayerViewport& viewport) = 0;
    virtual void update(Level& level, double deltaT) = 0;

    void body(b2Body* newBody) {
        body_ = newBody;
    }

    virtual void startContact(GameObject* other) {

    }

    virtual void endContact(GameObject* other) {

    }

    virtual bool hittable() const {
        return true;
    }

    b2Body* body() {
        return body_;
    }

    Level& level() {
        return *level_;
    }

    virtual bool isCover() const {
        return false;
    }

    const b2Vec2& position() const {
        return body_->GetPosition();
    }

    virtual void damage(const b2Vec2& hitPos) {
    }

};


#endif //SHOOTER_GAMEOBJECT_H
