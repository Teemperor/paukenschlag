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
#include <Character.h>

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

void PlayerViewport::addEffect(Level& level, const EffectData& data) {
    effects_.push_back(Effect(level.time(), data));
}

void PlayerViewport::renderUI() {
    window_.setView(window_.getDefaultView());
    status.draw(window_, 0, 0);
    if (player_) {
        sf::Sprite crosshair = player_->currentItem().crosshair();

        auto mousePos = sf::Mouse::getPosition(window_);
        crosshair.setPosition(mousePos.x, mousePos.y);
        crosshair.setColor(sf::Color::Red);
        window_.draw(crosshair);
    }
}

void PlayerViewport::apply() {
    view_.setCenter(player_->position().x * SCALE, player_->position().y * SCALE);
    window_.setView(view_);
}