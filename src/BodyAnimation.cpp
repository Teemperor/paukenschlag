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


#include "BodyAnimation.h"

void BodyAnimation::drawItem(Item& currentItem, PlayerViewport &viewport, const b2Vec2& position, double angle, b2Vec2 itemOffset, double alpha) {
    itemOffset.x /= SCALE;
    itemOffset.y /= SCALE;
    b2Vec2 itemPosition = {(float32) (position.x + std::cos(angle) * itemOffset.x - std::sin(angle) * itemOffset.y),
                           (float32) (position.y + std::sin(angle) * itemOffset.x + std::cos(angle) * itemOffset.y)};

    sf::Sprite& sprite = currentItem.showBurst(viewport.level().time()) ? currentItem.burstSprite() : currentItem.sprite();

    sprite.setPosition(itemPosition.x * SCALE, itemPosition.y * SCALE);
    sprite.setRotation((float) (angle * 180 / b2_pi));
    sprite.setColor(sf::Color(255, 255, 255, (sf::Uint8) (255 * alpha)));
    viewport.window().draw(sprite);
}