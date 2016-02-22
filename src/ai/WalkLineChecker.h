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


#ifndef SHOOTER_WALKLINECHECKER_H
#define SHOOTER_WALKLINECHECKER_H


#include <Box2D/Dynamics/b2WorldCallbacks.h>

class Level;

class WalkLineChecker : public b2RayCastCallback {

    bool lineIsFree_ = true;

public:
    static bool isFree(Level& level, b2Vec2& start, b2Vec2& end);

    virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                  const b2Vec2& normal, float32 fraction);
};


#endif //SHOOTER_WALKLINECHECKER_H
