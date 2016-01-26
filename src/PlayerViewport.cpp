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


#include "PlayerViewport.h"
#include "Level.h"


void PlayerViewport::addEffect(Level& level, b2Vec2 point, float rotation) {
    effects_.push_back(Effect(level.time(), point, rotation));
}

void PlayerViewport::renderEffects(Level& level) {
    for (Effect& effect : effects_) {
        effect.render(*this, level.time());
    }
    while (true) {
        if (effects_.empty())
            break;
        if (effects_.front().outOfTime(level.time())) {
            effects_.erase(effects_.begin());
        } else
            break;
    }
}