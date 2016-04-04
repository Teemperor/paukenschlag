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


#ifndef SHOOTER_CONSTANTS_H
#define SHOOTER_CONSTANTS_H

/* We need this to easily convert between pixel and real-world coordinates*/
const float SCALE = 32.f;

enum objectCategory {
    THING =          0x0001,
    WALL =          0x0002,
    ENEMY =          0x0004,
};

#endif //SHOOTER_CONSTANTS_H
