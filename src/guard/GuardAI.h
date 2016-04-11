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


#ifndef SHOOTER_GUARDAI_H
#define SHOOTER_GUARDAI_H


#include <Box2D/Common/b2Math.h>
#include <list>
#include <memory>
#include "GuardTask.h"

class Level;
class Soldier;

class GuardAI {

    std::unique_ptr<GuardTask> task_;

    double suspicion_ = 0;
    double nextHeadAdjustTime = 0;

    void checkPlayerVisibility(Soldier& guard, Level& level, double deltaT);

    bool alarmed_ = false;

    std::list<Soldier*> visiblePlayers_;
    b2Vec2 lastKnownPlayerPos_ = {0, 0};
    b2Vec2 lastSound_ = {0, 0};

    bool hasKnownPlayerPos() {
        return lastKnownPlayerPos_.x != 0 && lastKnownPlayerPos_.y != 0;
    }

    bool hasLastSound() {
        return lastSound_.x != 0 && lastSound_.y != 0;
    }

    static constexpr double fieldOfView_ = b2_pi * 0.8;

public:
    GuardAI();

    void update(Soldier& guard, Level& level, double deltaT);

    void modSuspicion(double diff) {
        suspicion_ += diff;
        if (suspicion_ < 0)
            suspicion_ = 0;
        else if (suspicion_ > 3)
            suspicion_ = 1;
    }

    double suspicion() const {
        if (suspicion_ > 1)
            return 1;
        return suspicion_;
    }

    std::list<Soldier*> visiblePlayers() {
        return visiblePlayers_;
    }

    double fieldOfView() {
        return fieldOfView_;
    }

};


#endif //SHOOTER_GUARDAI_H
