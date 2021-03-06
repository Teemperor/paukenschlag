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


#ifndef SHOOTER_INGAMESTATE_H
#define SHOOTER_INGAMESTATE_H


#include <Level.h>
#include <Cover.h>
#include <Crate.h>
#include <Hideaway.h>
#include <goals/EscapeArea.h>
#include <guard/Soldier.h>
#include <Door.h>
#include <levelgen/LevelGenerator.h>
#include "GameState.h"

class IngameState : public GameState {

    Level level;

    Soldier* character;

    PlayerViewport viewport;

public:
    IngameState(sf::RenderWindow& window) : viewport(&level, window) {

        character = new Soldier(level, 2 * SCALE, 2 * SCALE);
        viewport.player(character);

        LevelGenerator generator(level);
        generator.generate();

        level.setViewport(viewport);
        level.updateNavGrid();
    }

    virtual void update(double deltaT) override {
        viewport.updateUI(deltaT);
        level.update(deltaT);
    }

    virtual void draw(sf::RenderTarget& target) override {
        viewport.apply();
        level.render(viewport);
        viewport.renderEffects(level);
        viewport.renderUI();
    }

    virtual void handleEvent(sf::Event& event) override {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            viewport.player()->pullTrigger();
        }
    }
};


#endif //SHOOTER_INGAMESTATE_H
