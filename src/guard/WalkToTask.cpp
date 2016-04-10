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


#include "WalkToTask.h"
#include "Soldier.h"

void WalkToTask::update(Soldier& guard, Level& level, double deltaT) {
    if (path == nullptr) {
        b2Vec2 start = guard.position();
        path = level.navGrid().searchPath(start, target_);
    }

    if (path->finished()) {
        if (path->positions.empty()) {
            finish();
            return;
        }

        b2Vec2 nextTarget = path->positions.front().node_->pos;

        guard.rotateTo(nextTarget);

        double distance = Utils::distance(guard.position(), nextTarget);

        if (distance > goalDistance) {
            guard.walkForward();
        } else {
            guard.stopWalking();
            path->positions.pop_front();
        }

        if (lastStuckCheck > level.time() + stuckCheckInterval) {
            lastStuckCheck = level.time();
            if (lastDistanceToTarget <= distance) {
                finish();
            }
            lastDistanceToTarget = distance;
        }
    }
}

WalkToTask::WalkToTask(const b2Vec2& target, double goalDistance) : target_(target), goalDistance(goalDistance) {
    lastDistanceToTarget = std::numeric_limits<double>::max();
}