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


#include "Effect.h"
#include "PlayerViewport.h"

void Effect::render(PlayerViewport& viewport, double time) {
    float progress = (float) ((time - startTime_) / data_.duration());
    if (progress > 1)
        progress = 1;
    if (data_.fadesIn())
        data_.sprite().setColor(sf::Color(255, 255, 255, (sf::Uint8) (progress * 255)));
    else if (data_.fadesOut())
        data_.sprite().setColor(sf::Color(255, 255, 255, (sf::Uint8) ((1 - progress) * 255)));
    if (data_.scalesIn())
        data_.sprite().setScale(progress, progress);
    viewport.window().draw(data_.sprite());
}