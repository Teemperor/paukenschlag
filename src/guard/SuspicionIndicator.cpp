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


#include "SuspicionIndicator.h"
#include <Level.h>

void SuspicionIndicator::update(Level& level, double deltaT) {
    if (alarmSwingFactor > 0) {
        alarmSwingFactor -= 0.1f * deltaT;
    } else {
        alarmSwingFactor = 0;
    }
}

void SuspicionIndicator::draw(PlayerViewport &viewport, float x, float y, double suspicion) {
    if (suspicion >= 1) {
        if (!isAlarmed) {
            alarmSwingFactor = 0.5;
        }
        isAlarmed = true;
        alarmSprite_.setPosition(x, y);
        alarmSprite_.setScale(1 + alarmSwingFactor, 1 + alarmSwingFactor);

        viewport.window().draw(alarmSprite_);
    } else {
        isAlarmed = false;
        suspicionSprite_.setColor(sf::Color((sf::Uint8) (suspicion * 255), 0, 0, (sf::Uint8) (suspicion * 255)));
        suspicionSprite_.setScale((float) suspicion, (float) suspicion);
        suspicionSprite_.setPosition(x, y);
        viewport.window().draw(suspicionSprite_);
    }
}