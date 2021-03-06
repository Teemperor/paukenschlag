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


#ifndef SHOOTER_SOUNDMANAGER_H
#define SHOOTER_SOUNDMANAGER_H
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <Box2D/Common/b2Math.h>
#include "PlayerViewport.h"

class PlayerViewport;

class SoundManager {

    std::unordered_map<std::string, sf::SoundBuffer*> soundBuffersByPath_;

    std::vector<sf::Sound*> soundCache_;

    virtual ~SoundManager() {
        for (auto& pair : soundBuffersByPath_) {
            delete pair.second;
        }
    }

    sf::Sound& getSoundCache() {
        for (auto& sound : soundCache_) {
            if (sound->getStatus() == sf::Sound::Stopped) {
                return *sound;
            }
        }
        soundCache_.push_back(new sf::Sound());
        return *soundCache_.back();
    }

    SoundManager() {

    }

    sf::SoundBuffer& getSoundBuffer(const std::string& path) {
        sf::SoundBuffer* soundBuffer;
        auto iter = soundBuffersByPath_.find(path);
        if (iter != soundBuffersByPath_.end()) {
            soundBuffer = iter->second;
        } else {
            soundBuffer = new sf::SoundBuffer();
            soundBuffer->loadFromFile(path);
            soundBuffersByPath_[path] = soundBuffer;
        }
        return *soundBuffer;
    }

    std::set<PlayerViewport*> viewports_;

    PlayerViewport * getClosestViewport(b2Vec2 pos);

public:
    static SoundManager& instance() {
        static SoundManager instance_;
        return instance_;
    }

    void addViewport(PlayerViewport* viewport) {
        viewports_.insert(viewport);
    }

    void removeViewport(PlayerViewport* viewport) {
        viewports_.erase(viewport);
    }

    void playSound(const std::string& path, b2Vec2 pos);
};


#endif //SHOOTER_SOUNDMANAGER_H
