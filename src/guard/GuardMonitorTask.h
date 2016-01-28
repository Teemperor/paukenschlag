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


#ifndef SHOOTER_GUARDMONITORTASK_H
#define SHOOTER_GUARDMONITORTASK_H


#include "GuardTask.h"

class GuardMonitorTask : public GuardTask {

public:
    virtual void update(Guard& guard, Level& level, double deltaT) override {

    }
};


#endif //SHOOTER_GUARDMONITORTASK_H
