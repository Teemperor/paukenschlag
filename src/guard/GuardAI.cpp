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


#include "GuardAI.h"
#include <Level.h>
#include <Character.h>
#include <LOSChecker.h>
#include "Guard.h"
#include "GuardMonitorTask.h"
#include "WanderTask.h"


static std::default_random_engine generator;
static std::uniform_real_distribution<float> headRotationDistribution(-0.7f, 0.7f);

void GuardAI::update(Guard& guard, Level& level, double deltaT) {

    if (level.time() > nextHeadAdjustTime) {
        nextHeadAdjustTime = level.time() + 1.5;
        guard.setHeadRotation(headRotationDistribution(generator));
    }

    task_->doUpdate(guard, level, deltaT);

    checkPlayerVisibility(guard, level, deltaT);

    /*if (Utils::distance(guard.body()->GetPosition(), walkTarget) > 3) {
        guard.body()->SetTransform(guard.body()->GetPosition(), (float32) atan2(walkTarget.y - guard.body()->GetPosition().y, walkTarget.x - guard.body()->GetPosition().x));
    }*/
}

void GuardAI::checkPlayerVisibility(Guard& guard, Level& level, double deltaT) {
    visiblePlayers_.clear();

    modSuspicion(-deltaT / 3.0f);

    guard.visible_ = false;

    for (Character* player : level.players()) {
        bool hasLOS = LOSChecker::canSee(level, guard.body()->GetPosition(), player->body());

        if (hasLOS)
            guard.visible_ = true;

        if (player->hidden()) {
            continue;
        }

        b2Vec2 toPlayer = player->position() - guard.position();
        double angle = std::atan2(toPlayer.y, toPlayer.x) - guard.getViewDirection();
        if (angle < 0)
            angle += b2_pi * 2;

        if (angle > fieldOfView_ / 2 && angle < b2_pi * 2 - fieldOfView_ / 2) {
            continue;
        }



        if (hasLOS) {
            visiblePlayers_.push_back(player);
            modSuspicion(deltaT / 1.0f);
        }
    }
}

GuardAI::GuardAI() {
    task_.reset(new GuardMonitorTask());
}