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


#include "SoundManager.h"
#include "Utils.h"

void SoundManager::playSound(const std::string& path, b2Vec2 pos) {
    if (path.empty())
        return;

    const double maxHearDistance = 50;

    PlayerViewport* viewport = getClosestViewport(pos);

    double distance = Utils::distance(viewport->centerPos(), pos);
    if (distance > maxHearDistance)
        distance = maxHearDistance;


    double volume = (maxHearDistance - distance) / maxHearDistance;
    volume = std::min(volume, 1.0);

    sf::SoundBuffer& buffer = getSoundBuffer(path);
    sf::Sound& sound = getSoundCache();
    sound.setVolume((float) (volume * 100.0f));

    // TODO remove
    sound.setVolume(0);

    sound.setBuffer(buffer);
    sound.play();
}

PlayerViewport *SoundManager::getClosestViewport(b2Vec2 pos) {
    PlayerViewport* result = nullptr;
    for (PlayerViewport* viewport : viewports_) {
        if (result == nullptr)
            result = viewport;
        else if (Utils::distance(viewport->centerPos(), pos) < Utils::distance(result->centerPos(), pos)) {
            result = viewport;
        }
    }
    return result;
}