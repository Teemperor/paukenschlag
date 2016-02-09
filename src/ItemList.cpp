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


#include "ItemList.h"

ItemList::ItemList() {
    items_[ItemId::Knife]
            .name("Knife")
            .icon("data/weapons/knife_icon.png")
            .fireInterval(0.2)
            .range(2)
            .itemClass(ItemClass::Knife)
            .sprite("data/weapons/knife.png", 4, 1);
    items_[ItemId::None]
            .name("Empty").itemClass(ItemClass::None);
    items_[ItemId::AK47]
            .name("AK-47")
            .icon("data/weapons/ak47_icon.png")
            .fireInterval(0.1)
            .range(100)
            .automatic(true)
            .bullets(30, 60, 2)
            .itemClass(ItemClass::Rifle)
            .emptySound("data/sounds/empty.wav")
            .crosshair("data/crosshairs/02.png")
            .useSound("data/sounds/ak47.wav")
            .sprite("data/weapons/ak47.png", 30, 4)
            .burstSprite("data/weapons/ak47_burst.png", 28, 9);
    items_[ItemId::Glock]
            .name("Glock")
            .icon("data/weapons/glock_icon.png")
            .burstSprite("data/weapons/glock_burst.png", 1, 8)
            .fireInterval(0.3)
            .range(60)
            .bullets(6, 18, 2)
            .itemClass(ItemClass::Pistol)
            .crosshair("data/crosshairs/03.png")
            .emptySound("data/sounds/empty.wav")
            .useSound("data/sounds/glock.wav")
            .sprite("data/weapons/glock.png", 2, 2);
    items_[ItemId::M14].name("M14")
            .icon("data/weapons/m14_icon.png")
            .fireInterval(0.1)
            .range(100)
            .precision(0.01)
            .itemClass(ItemClass::Rifle)
            .emptySound("data/sounds/empty.wav")
            .sprite("data/weapons/m14.png", 30, 2)
            .burstSprite("data/weapons/m14_burst.png", 30, 9);
    items_[ItemId::Pistol9mmSilenced]
            .name("9mm (Silenced)")
            .icon("data/weapons/9mm_silenced_icon.png")
            .fireInterval(0.2)
            .range(40)
            .emptySound("data/sounds/empty.wav")
            .precision(0.01)
            .itemClass(ItemClass::Pistol)
            .useSound("data/sounds/silenced.wav")
            .sprite("data/weapons/9mm.png", 1, 2)
            .crosshair("data/crosshairs/03.png")
            .burstSprite("data/weapons/9mm_burst.png", 1, 6);

    for (auto& pair : items_) {
        pair.second.id(pair.first);
    }
}