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


#include "PlayerStatus.h"
#include <Item.h>
#include "Character.h"

void PlayerStatus::draw(sf::RenderTarget& target, float x, float y) {
    x += itemCircle.getLocalBounds().width + radius;
    y += itemCircle.getLocalBounds().height + radius;

    renderCircle(character->items()[0], target, x, y - radius, character->selectedItemIndex() == 0);
    renderCircle(character->items()[1], target, x + radius, y, character->selectedItemIndex() == 1);
    renderCircle(character->items()[2], target, x, y + radius, character->selectedItemIndex() == 2);
    renderCircle(character->items()[3], target, x - radius, y, character->selectedItemIndex() == 3);
}

void PlayerStatus::renderCircle(Item& item, sf::RenderTarget& target, float x, float y, bool active) {
    itemCircle.setPosition(x, y);
    if (active)
        itemCircle.setColor(sf::Color::Red);
    else
        itemCircle.setColor(sf::Color::Green);
    target.draw(itemCircle);
    sf::Sprite& icon = item.icon();
    icon.setPosition(x, y);
    target.draw(icon);
}