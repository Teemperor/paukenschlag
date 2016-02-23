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


#ifndef SHOOTER_LOSCHECKER_H
#define SHOOTER_LOSCHECKER_H

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <limits>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>

class Level;

class LOSChecker : public b2RayCastCallback {

    b2Vec2 start;
    b2Body* target;
    double totalDistance;
    double targetDistance = 0;
    double closestDistance = std::numeric_limits<double>::max();

    bool seesTarget() {
        return closestDistance > targetDistance;
    }

public:
    static bool canSee(Level&level, const b2Vec2& start, b2Body* body);

    virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                  const b2Vec2& normal, float32 fraction);

};


#endif //SHOOTER_LOSCHECKER_H
