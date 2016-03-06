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
#include <Character.h>
#include <Cover.h>
#include <Crate.h>
#include <Hideaway.h>
#include <goals/EscapeArea.h>
#include <guard/Guard.h>
#include "GameState.h"

class IngameState : public GameState {

    Level level;

    Character* character;

    PlayerViewport viewport;

public:
    IngameState(sf::RenderWindow& window) : viewport(&level, window) {

        character = new Character(level, 950, 950);
        viewport.player(character);


        for (int i = 0; i < 10; i++) {
            int x = Utils::rndGen() % 2000;
            int y = Utils::rndGen() % 2000;
            new Wall(level, x, y);
        }

        new Cover(level, 300, 600);

        new Crate(level, 100, 100);
        for (int i = 0; i < 17; i++)
            new Hideaway(level, 350 + i * 40, 350 + i * 40);
        new EscapeArea(level, 350, 150);

        for (int i = 0; i < 10; i++)
            new Guard(level, 1080 + 80 * i, 1000);
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
            viewport.player()->pulledTrigger();
        }
    }
};


#endif //SHOOTER_INGAMESTATE_H
