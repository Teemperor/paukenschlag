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


#ifndef SHOOTER_LEVEL_H
#define SHOOTER_LEVEL_H

#include <Box2D/Box2D.h>
#include <list>
#include <iostream>
#include <ai/NavGrid.h>
#include "GameObject.h"
#include <sfbl/sfbl.h>

class Character;

class Level : b2ContactListener {

    b2World world_;
    std::list<GameObject*> objects_;
    std::list<Character*> players_;
    double time_ = 0;
    PlayerViewport* viewport_;

    sf::Sprite dirtySprite;
    sf::Sprite sandSprite;
    sf::Sprite alphaSprite;

    sf::Shader shader;
    sf::RenderTexture alphaTexture;

    NavGrid navGrid_;


public:
    Level();

    virtual void BeginContact(b2Contact* contact) override {
        GameObject* objectA = (GameObject*) contact->GetFixtureA()->GetUserData();
        GameObject* objectB = (GameObject*) contact->GetFixtureB()->GetUserData();
        objectA->startContact(objectB);
        objectB->startContact(objectA);
    }

    virtual void EndContact(b2Contact* contact) override {
        GameObject* objectA = (GameObject*) contact->GetFixtureA()->GetUserData();
        GameObject* objectB = (GameObject*) contact->GetFixtureB()->GetUserData();
        objectA->endContact(objectB);
        objectB->endContact(objectA);
    }

    void updateNavGrid() {
        navGrid_.setLevel(this);
    }

    NavGrid& navGrid() {
        return navGrid_;
    }

    void render(PlayerViewport& viewport);

    void setViewport(PlayerViewport& viewport) {
        viewport_ = &viewport;
    }

    void update(double deltaT);

    void add(GameObject* object) {
        objects_.push_back(object);
    }

    void add(Character* object);

    b2World& world() {
        return world_;
    }

    double time() const {
        return time_;
    }

    PlayerViewport& viewport() {
        return *viewport_;
    }

    std::list<Character*>& players() {
        return players_;
    }
};


#endif //SHOOTER_LEVEL_H
