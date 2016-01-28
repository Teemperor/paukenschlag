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


#ifndef SHOOTER_GUARDTASK_H
#define SHOOTER_GUARDTASK_H

class Guard;
class Level;

class GuardTask {
public:
    virtual GuardTask* update(Guard& guard, Level& level, double deltaT) = 0;
};


#endif //SHOOTER_GUARDTASK_H
