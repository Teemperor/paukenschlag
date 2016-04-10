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


#include "WanderTask.h"
#include "Soldier.h"
#include "WalkToTask.h"
#include "WaitTask.h"

static std::default_random_engine generator;
static std::uniform_real_distribution<float> headRotationDistribution(-15.7f, 15.7f);

void WanderTask::update(Soldier& guard, Level& level, double deltaT) {

    if (isWalking) {
        isWalking = false;
        childTask(new WaitTask(3));
    } else {
        isWalking = true;
        b2Vec2 target = guard.position();
        target.x += headRotationDistribution(generator);
        target.y += headRotationDistribution(generator);

        childTask(new WalkToTask(target));
    }

}