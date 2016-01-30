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


#ifndef SHOOTER_EFFECT_H
#define SHOOTER_EFFECT_H


#include <SFML/Graphics/Sprite.hpp>
#include <Box2D/Common/b2Settings.h>
#include <Box2D/Common/b2Math.h>
#include "Constants.h"
#include "TextureManager.h"
#include "EffectData.h"

class PlayerViewport;

class Effect {

    EffectData data_;
    double startTime_;

public:
    Effect(double time, const EffectData& data) : data_(data) {
        startTime_ = time;
    }

    virtual void render(PlayerViewport& viewport, double time);

    bool outOfTime(double currentTime) {
        return startTime_ + data_.duration() < currentTime;
    }

};


#endif //SHOOTER_EFFECT_H
