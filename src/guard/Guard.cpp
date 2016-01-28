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


void Guard::update(Level& level, double deltaT) {
    if (!dead_) {
        ai_.update(*this, level, deltaT);
        double headRotationDiff = headRotationTarget - headRotation;

        double headRotationChange = deltaT;

        if (std::abs(headRotationDiff) < headRotationChange) {
            headRotation = headRotationTarget;
        } else {
            if (headRotationTarget > headRotation) {
                headRotation += headRotationChange;
            } else {
                headRotation -= headRotationChange;
            }
        }
    }
}
