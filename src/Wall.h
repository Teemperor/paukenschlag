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


#ifndef SHOOTER_GROUND_H
#define SHOOTER_GROUND_H


#include "GameObject.h"
#include "TextureManager.h"
#include "Level.h"

class Wall : public GameObject {

    sf::Sprite sprite_;
    sf::Sprite spriteStart_;
    sf::Sprite spriteEnd_;
    float length_;
    float angle_;
    b2Vec2 start_;

public:
    Wall(Level& level, const b2Vec2& start, const b2Vec2& end, const std::string& filePath);

    constexpr static float halfWallWidth = 0.2f;

    virtual bool blocksView() const override{
        return true;
    }

    virtual bool isObstacle() const override {
        return true;
    }

    virtual void render(PlayerViewport& viewport);

    virtual void update(Level& level, double deltaT) override {
    }
};


#endif //SHOOTER_GROUND_H
