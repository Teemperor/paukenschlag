
#include "NavGrid.h"
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