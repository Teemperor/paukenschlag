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
#include <Character.h>
#include "GuardTask.h"

class Level;
class Guard;

class GuardAI {

    std::unique_ptr<GuardTask> task_;

    double suspicion_ = 0;
    double nextHeadAdjustTime = 0;
    double fieldOfView = b2_pi;

    void checkPlayerVisibility(Guard& guard, Level& level, double deltaT);

public:
    GuardAI();

    void update(Guard& guard, Level& level, double deltaT);

    void modSuspicion(double diff) {
        suspicion_ += diff;
        if (suspicion_ < 0)
            suspicion_ = 0;
        else if (suspicion_ > 3)
            suspicion_ = 1;
    }

    double suspicioun() const {
        return suspicion_;
    }

};


#endif //SHOOTER_GUARDAI_H
