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


#ifndef SHOOTER_WALKTOTASK_H
#define SHOOTER_WALKTOTASK_H


#include <Box2D/Common/b2Math.h>
#include <ai/AStarPath.h>
#include "GuardTask.h"

class WalkToTask : public GuardTask {

    b2Vec2 target_;
    double lastDistanceToTarget = 0;
    double stuckCheckInterval = 1;
    double lastStuckCheck = 0;
    double goalDistance = 0.3;

    AStarPath* path = nullptr;

public:
    WalkToTask(const b2Vec2& target, double goalDistance = 0.3);
    virtual void update(Guard& guard, Level& level, double deltaT);
};


#endif //SHOOTER_WALKTOTASK_H
