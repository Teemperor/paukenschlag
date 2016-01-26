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


#include "Guard.h"
#include "Character.h"
#include "Utils.h"

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

void Guard::update(Level& level) {
    for (Character* player : level.players()) {
        b2Vec2 toPlayer = player->position() - position();
        double angle = std::atan2(toPlayer.y, toPlayer.x) - body()->GetAngle();
        if (angle < 0)
            angle += b2_pi * 2;

        if (angle > b2_pi / 2 && angle < b2_pi * 2 - b2_pi / 2) {
            modSuspicion(-0.01f);
            continue;
        }

        LOSRaycaster raycaster;
        raycaster.start = body()->GetPosition();
        raycaster.target = player->body()->GetFixtureList();

        level.world().RayCast(&raycaster, body()->GetPosition(), player->body()->GetPosition());

        if (raycaster.seesTarget()) {
            modSuspicion(0.01f);
        } else {
            modSuspicion(-0.01f);
        }
    }

    if (Utils::distance(body()->GetPosition(), walkTarget) > 3) {
        body()->SetTransform(body()->GetPosition(), (float32) atan2(walkTarget.y - body()->GetPosition().y, walkTarget.x - body()->GetPosition().x));
    }

    if (suspicion >= 1)
        weapon.tryShoot(position(), body()->GetAngle());
}
