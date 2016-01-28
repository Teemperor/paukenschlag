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

#include <memory>

class Guard;
class Level;

class GuardTask {

    std::unique_ptr<GuardTask> childTask_;
    bool finished_ = false;

public:
    virtual void update(Guard& guard, Level& level, double deltaT) = 0;

    void doUpdate(Guard& guard, Level& level, double deltaT) {
        if (childTask_) {
            childTask_->doUpdate(guard, level, deltaT);
            if (childTask_->finished()) {
                childTask_.reset(nullptr);
            }
            passiveUpdate(guard, level, deltaT);
        }
        else
            update(guard, level, deltaT);
    }

    virtual GuardTask* childTask() {
        if (childTask_)
            return childTask_.get();
        return nullptr;
    }

    void childTask(GuardTask* guardTask) {
        childTask_.reset(guardTask);
    }

    void finish() {
        finished_ = true;
    }

    bool finished() {
        return finished_;
    }

    virtual GuardTask* passiveUpdate(Guard& guard, Level& level, double deltaT) {

    }

};


#endif //SHOOTER_GUARDTASK_H
