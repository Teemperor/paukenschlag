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
#include "GameObject.h"
class Character;

class Level : b2ContactListener {

    b2World world_;
    std::list<GameObject*> objects_;
    std::list<Character*> players_;
    double time_ = 0;
    PlayerViewport* viewport_;

    sf::Sprite dirtySprite;

public:
    Level() : world_(b2Vec2(0.f, 0.f)) {
        dirtySprite = TextureManager::instance().loadSprite("data/floor/sand.jpg");
        world_.SetContactListener(this);
    }


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

    void render(PlayerViewport& viewport) {
        int x1 = ((int) (viewport.view().getCenter().x - viewport.view().getSize().x / 2) / (int) dirtySprite.getLocalBounds().width);
        int y1 = ((int) (viewport.view().getCenter().y - viewport.view().getSize().y / 2) / (int) dirtySprite.getLocalBounds().height);
        int x2 = ((int) (viewport.view().getCenter().x + viewport.view().getSize().x / 2) / (int) dirtySprite.getLocalBounds().width);
        int y2 = ((int) (viewport.view().getCenter().y + viewport.view().getSize().y / 2) / (int) dirtySprite.getLocalBounds().height);


        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                dirtySprite.setPosition(x * dirtySprite.getLocalBounds().width, y * dirtySprite.getLocalBounds().height);
                viewport.window().draw(dirtySprite);
            }
        }

        for (GameObject* object : objects_) {
            object->render(viewport);
        }
    }

    void setViewport(PlayerViewport& viewport) {
        viewport_ = &viewport;
    }

    void update() {
        world_.Step(1 / 60.f, 8, 3);
        time_ += 1 / 60.0f;
        for (GameObject* object : objects_) {
            object->update(*this, 1 / 60.0f);
        }
    }

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
