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


#ifndef SHOOTER_SUSPICIONINDICATOR_H
#define SHOOTER_SUSPICIONINDICATOR_H

#include "PlayerViewport.h"

class SuspicionIndicator {

    sf::Sprite suspicionSprite_;
    sf::Sprite alarmSprite_;

    bool isAlarmed = false;
    float alarmSwingFactor = 0;

public:
    SuspicionIndicator() {
        suspicionSprite_ = TextureManager::instance().loadSprite("data/emotes/suspicion.png");
        suspicionSprite_.setOrigin(10, 44);
        alarmSprite_ = TextureManager::instance().loadSprite("data/emotes/alarm.png");
        alarmSprite_.setOrigin(2, 42);
    }

    void update(Level& level, double deltaT);

    void draw(PlayerViewport &viewport, float x, float y, double suspicion);
};


#endif //SHOOTER_SUSPICIONINDICATOR_H
