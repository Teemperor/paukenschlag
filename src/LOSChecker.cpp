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


#include "LOSChecker.h"
#include <Level.h>

float32 LOSChecker::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                          const b2Vec2& normal, float32 fraction) {
    GameObject* object = static_cast<GameObject*>(fixture->GetUserData());

    double d = Utils::distance(start, point);

    if (fixture->GetBody() == target) {
        targetDistance = d;
    } else if (!object->transparent()){
        if (d < closestDistance) {
            closestDistance = d;
        }
    }

    return (float32) (d / totalDistance);
}

bool LOSChecker::canSee(Level&level, const b2Vec2& start, b2Body* body) {
    LOSChecker checker;
    checker.target = body;
    checker.start = start;
    checker.totalDistance = Utils::distance(start, body->GetPosition());
    level.world().RayCast(&checker, start, body->GetPosition());
    return checker.seesTarget();
}