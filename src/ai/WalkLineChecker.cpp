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


#include "WalkLineChecker.h"
#include <Level.h>

const std::vector<float> checkOffsets = {-1.1f, 0, 1.1f};

bool WalkLineChecker::isFree(Level& level, b2Vec2& start, b2Vec2& end) {
    for (float xOffset : checkOffsets) {
        for (float yOffset : checkOffsets) {
            b2Vec2 currentStart = {start.x + xOffset, start.y + yOffset};
            b2Vec2 currentEnd = {end.x + xOffset, end.y + yOffset};
            WalkLineChecker checker;
            level.world().RayCast(&checker, currentStart, currentEnd);
            if (!checker.lineIsFree_) {
                return false;
            }
        }
    }
    return true;
}

float32 WalkLineChecker::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                               const b2Vec2& normal, float32 fraction) {

    GameObject* object = static_cast<GameObject*>(fixture->GetUserData());


    if (object->isObstacle()) {
        lineIsFree_ = false;
        return 0;
    }

    return -1;
}