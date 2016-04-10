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


#include "GuardMonitorTask.h"
#include "WanderTask.h"
#include "GuardAI.h"
#include "Soldier.h"
#include "GuardCombatTask.h"

void GuardMonitorTask::update(Soldier& guard, Level& level, double deltaT) {
    inCombat = false;
    childTask(new WanderTask());
}

void GuardMonitorTask::passiveUpdate(Soldier& guard, Level& level, double deltaT) {
    if (!inCombat && !guard.ai().visiblePlayers().empty()) {
        if (guard.ai().suspicion() >= 1) {
            childTask(new GuardCombatTask());
            inCombat = true;
        }
    }
}