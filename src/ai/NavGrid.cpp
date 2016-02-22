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


#include "NavGrid.h"
#include "SensorRectangle.h"
#include "AStarPath.h"
#include <Level.h>

AStarPath *NavGrid::searchPath(b2Vec2& start, b2Vec2& end) {
    unsigned startXInt = (unsigned int) (start.x / gridSpacing_);
    unsigned startYInt = (unsigned int) (start.y / gridSpacing_);

    if (startXInt >= nodes_.size())
        startXInt = nodes_.size() - 1;

    if (startYInt >= nodes_[startXInt].size())
        startYInt = nodes_[startXInt].size() - 1;

    NavNode* startNode = nodes_[startXInt][startYInt];

    unsigned endXInt = (unsigned int) (end.x / gridSpacing_);
    unsigned endYInt = (unsigned int) (end.y / gridSpacing_);

    if (endXInt >= nodes_.size())
        endXInt = nodes_.size() - 1;

    if (endYInt >= nodes_[endXInt].size())
        endYInt = nodes_[endXInt].size() - 1;

    NavNode* endNode = nodes_[endXInt][endYInt];

    AStarPath* result = AStarPath::create(level_, startNode, endNode);

    return result;
}