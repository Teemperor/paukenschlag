

#ifndef SHOOTER_ASTARPATH_H
#define SHOOTER_ASTARPATH_H

#include <list>
#include <chrono>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <Box2D/Dynamics/b2Body.h>
#include <Constants.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <GameObject.h>
#include <stlastar.h>
#include "NavGrid.h"

struct MapSearchNode {
    const NavNode* node_;

    MapSearchNode(const NavNode* node = nullptr) : node_(node) {
    }

    float GoalDistanceEstimate(MapSearchNode &nodeGoal);
    bool IsGoal(MapSearchNode &nodeGoal);
    bool GetSuccessors(AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node);
    float GetCost(MapSearchNode &successor);
    bool IsSameState(MapSearchNode &rhs);
};

class AStarPath
{
    static std::list<AStarPath*> instances;

    Level* level;

    bool finished_ = false;

    AStarSearch<MapSearchNode> astarsearch;

    MapSearchNode startNode_, endNode_;

public:
    std::list<MapSearchNode> positions;

    virtual ~AStarPath() {
        instances.remove(this);
    }

    static AStarPath* create(Level* level, MapSearchNode start, MapSearchNode end) {
        AStarPath* result = new AStarPath();
        result->level = level;
        result->astarsearch.SetStartAndGoalStates(start, end);
        result->startNode_ = start;
        result->endNode_ = end;

        instances.push_back(result);

        return result;
    }

    void process(std::chrono::steady_clock::time_point timeLimit);

    bool finished() {
        return finished_;
    }

    static void processGlobal(std::chrono::steady_clock::time_point timeLimit) {
        if (!instances.empty())
            instances.front()->process(timeLimit);
    }
};


#endif //SHOOTER_ASTARPATH_H
