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


#ifndef SHOOTER_TEXTUREMANAGER_H
#define SHOOTER_TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>

class TextureManager {

    std::map<std::string, sf::Texture*> texturesByPath_;

public:
    static TextureManager& instance() {
        static TextureManager instance_;
        return instance_;
    }

    sf::Sprite loadSprite(const std::string& path) {
        sf::Texture* texture;
        auto iter = texturesByPath_.find(path);
        if (iter != texturesByPath_.end()) {
            texture = iter->second;
        } else {
            texture = new sf::Texture();
            texture->loadFromFile(path);
            texturesByPath_[path] = texture;
        }
        sf::Sprite result(*texture);

        return result;
    }
};


#endif //SHOOTER_TEXTUREMANAGER_H
