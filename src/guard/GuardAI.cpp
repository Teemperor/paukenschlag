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
#include "Guard.h"
#include "GuardMonitorTask.h"



static std::default_random_engine generator;
static std::uniform_real_distribution<float> headRotationDistribution(-0.7f, 0.7f);

class LOSRaycaster : public b2RayCastCallback {
public:
    b2Vec2 start;
    b2Fixture* target;
    double targetDistance = 0;
    double closestDistance = std::numeric_limits<double>::max();

    virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                  const b2Vec2& normal, float32 fraction) override {
        if (fixture == target) {
            targetDistance = Utils::distance(start, point);
        } else {
            double d = Utils::distance(start, point);
            if (d < closestDistance) {
                closestDistance = d;
            }
        }

        return -1;
    }

    bool seesTarget() {
        return closestDistance > targetDistance;
    }
};

void GuardAI::update(Guard& guard, Level& level, double deltaT) {

    if (level.time() > nextHeadAdjustTime) {
        nextHeadAdjustTime = level.time() + 3;
        guard.setHeadRotation(headRotationDistribution(generator));
    }

    GuardTask* newTask = task_->update(guard, level, deltaT);

    if (newTask != task_.get()) {
        task_.reset(newTask);
    }

    checkPlayerVisibility(guard, level, deltaT);

    /*if (Utils::distance(guard.body()->GetPosition(), walkTarget) > 3) {
        guard.body()->SetTransform(guard.body()->GetPosition(), (float32) atan2(walkTarget.y - guard.body()->GetPosition().y, walkTarget.x - guard.body()->GetPosition().x));
    }*/

    if (suspicion_ >= 1)
        guard.weapon().tryShoot(guard.position(), guard.body()->GetAngle());
}

void GuardAI::checkPlayerVisibility(Guard& guard, Level& level, double deltaT) {
    modSuspicion(-deltaT / 3.0f);

    for (Character* player : level.players()) {
        if (player->hidden()) {
            continue;
        }

        b2Vec2 toPlayer = player->position() - guard.position();
        double angle = std::atan2(toPlayer.y, toPlayer.x) - guard.getViewDirection();
        if (angle < 0)
            angle += b2_pi * 2;

        if (angle > fieldOfView / 2 && angle < b2_pi * 2 - fieldOfView / 2) {
            continue;
        }

        LOSRaycaster raycaster;
        raycaster.start = guard.body()->GetPosition();
        raycaster.target = player->body()->GetFixtureList();

        level.world().RayCast(&raycaster, guard.body()->GetPosition(), player->body()->GetPosition());

        if (raycaster.seesTarget()) {
            modSuspicion(deltaT / 1.0f);
        }
    }
}

GuardAI::GuardAI() {
    task_.reset(new GuardMonitorTask());
}