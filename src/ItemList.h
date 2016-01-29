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


#ifndef SHOOTER_ITEMLIST_H
#define SHOOTER_ITEMLIST_H


#include "Item.h"

class ItemList {

    std::map<ItemId, Item> items_;

    ItemList();

public:
    static const ItemList& instance() {
        static ItemList instance_;
        return instance_;
    }

    const Item& item(ItemId id) const {
        return items_.find(id)->second;
    }

    static const Item& get(ItemId id) {
        return instance().item(id);
    }
};


#endif //SHOOTER_ITEMLIST_H
