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


#ifndef SHOOTER_UTILS_H
#define SHOOTER_UTILS_H


#include <Box2D/Common/b2Math.h>
#include <cmath>

class Utils {

public:

    static double distance(const b2Vec2& start, const b2Vec2& end) {
        double diffX = start.x - end.x;
        double diffY = start.y - end.y;
        return sqrt(diffX * diffX + diffY * diffY);
    }

    static double dotProduct(const b2Vec2& a, const b2Vec2& b) {
        return a.x * b.x + a.y * b.y;
    }

    static double length(const b2Vec2& v) {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }
};


#endif //SHOOTER_UTILS_H
