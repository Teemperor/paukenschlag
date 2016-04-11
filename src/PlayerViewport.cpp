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
#include "SoundManager.h"
#include <guard/Soldier.h>

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
    window().setView(window().getDefaultView());
    //worldLight_->setViewportPos(player_->position().x - window().getView().getSize().x / 2 / SCALE, player_->position().y - window().getView().getSize().y / 2 / SCALE);
    //worldLight_->updateSpotLight(&player_->fieldOfView());
    //worldLight_->updateNrender();
}

void PlayerViewport::addEffect(Level& level, const EffectData& data) {
    effects_.push_back(Effect(level.time(), data));
}

void PlayerViewport::renderUI() {
    apply();
    if (player_) {
        auto mousePos = sf::Mouse::getPosition(window_);
        b2Vec2 mousePosFromCenter = {mousePos.x - view_.getSize().x / 2, mousePos.y - view_.getSize().y / 2};

        b2Vec2 ingameMousePos = {player_->position().x + mousePosFromCenter.x / SCALE,
                                 player_->position().y + mousePosFromCenter.y / SCALE};

        sf::Sprite crosshair = player_->currentItem().crosshair();

        Item::Raycaster raycaster;
        raycaster.start = player_->position();

        player_->level().world().RayCast(&raycaster, raycaster.start, ingameMousePos);

        crosshair.setPosition(ingameMousePos.x * SCALE, ingameMousePos.y * SCALE);
        crosshair.setColor(sf::Color::Red);
        window_.draw(crosshair);

        if (raycaster.target) {
            crosshair.setPosition(raycaster.point.x * SCALE, raycaster.point.y * SCALE);
            crosshair.setColor(sf::Color(222, 222, 222, 255));
            window_.draw(crosshair);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        view_.zoom(1.001f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        view_.zoom(0.999f);

    window_.setView(window_.getDefaultView());
    status.draw(window_, 0, 0);
}

void PlayerViewport::apply() {
    float newCenterX = player_->position().x * SCALE;
    float newCenterY = player_->position().y * SCALE;

    /*if (newCenterX - view_.getSize().x / 2 < 0) {
        newCenterX = view_.getSize().x / 2;
    }

    if (newCenterY - view_.getSize().y / 2 < 0) {
        newCenterY = view_.getSize().y / 2;
    }*/

    view_.setCenter(newCenterX, newCenterY);
    window_.setView(view_);
}

PlayerViewport::PlayerViewport(Level* level, sf::RenderWindow& window) : window_(window),
                                                                         view_(sf::Vector2f(window_.getSize().x / 2, window_.getSize().y / 2),
                                                                               sf::Vector2f(window_.getSize().x, window_.getSize().y)),
                                                                         level_(level) {
    SoundManager::instance().addViewport(this);

    if (!worldLight_) {
        worldLight_.reset(new sfbl::WorldLight(&level->world(), &window_));
        worldLight_->setDarkness(10);
    }
}

PlayerViewport::~PlayerViewport() {
    SoundManager::instance().removeViewport(this);
}

void PlayerViewport::player(Soldier* player) {
    player_ = player;
    status = PlayerStatus(player);
    player_->setIsPlayer(true);
}