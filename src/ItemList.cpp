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
    items_[ItemId::Knife].name("Knife").icon("data/weapons/knife.png").fireInterval(0.5).range(2);
    items_[ItemId::None].name("Empty");
    items_[ItemId::AK47].name("AK-47").icon("data/weapons/ak47_icon.png");
    items_[ItemId::M14].name("M14").icon("data/weapons/m14_icon.png");
    items_[ItemId::Pistol9mmSilenced].name("9mm (Silenced)").icon("data/weapons/9mm_silenced_icon.png");

    for (auto& pair : items_) {
        pair.second.id(pair.first);
    }
}