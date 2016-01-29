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


#ifndef SHOOTER_GAMESTATE_H
#define SHOOTER_GAMESTATE_H


#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

class GameState {
public:
    virtual void update(double deltaT) {
    }
    virtual void draw(sf::RenderTarget& target) {
    }
    virtual void handleEvent(sf::Event& event) {
    }

};


#endif //SHOOTER_GAMESTATE_H
