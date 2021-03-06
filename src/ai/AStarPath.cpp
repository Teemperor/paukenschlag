
#include "AStarPath.h"

bool MapSearchNode::IsSameState(MapSearchNode& rhs) {
    return node_ == rhs.node_;
}

float MapSearchNode::GoalDistanceEstimate(MapSearchNode& nodeGoal) {
    return fabs(node_->pos.x - nodeGoal.node_->pos.x) + fabs(node_->pos.y - nodeGoal.node_->pos.y);
}

bool MapSearchNode::IsGoal(MapSearchNode& nodeGoal) {
    return nodeGoal.node_ == node_;
}

bool MapSearchNode::GetSuccessors(AStarSearch<MapSearchNode>* astarsearch, MapSearchNode* parent_node) {
    for (const NavNode* node : node_->neighbours()) {
        if (parent_node == nullptr || node != parent_node->node_) {
            MapSearchNode mapNode(node);
            astarsearch->AddSuccessor(mapNode);
        }
    }
    return true;
}

float MapSearchNode::GetCost(MapSearchNode& successor) {
    return 1;
}

std::list<AStarPath*> AStarPath::instances;

void AStarPath::process(std::chrono::steady_clock::time_point timeLimit) {
    unsigned int SearchState;

    do {
        if (std::chrono::steady_clock::now() > timeLimit)
            return;

        SearchState = astarsearch.SearchStep();
    } while (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING);

    if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED) {
        astarsearch.GetSolutionStart();

        int steps = 0;

        // We don't add the start node, that would make no sense...
        //positions.push_back(TilePosition(node->x, node->y));
        while (true)
        {
            auto node = astarsearch.GetSolutionNext();

            if (!node)
            {
                break;
            }

            positions.push_back(*node);
            steps ++;
        }

        // Once you're done with the solution you can free the nodes up
        astarsearch.FreeSolutionNodes();
    }
    else if (SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED) {
        std::cerr << "Failed to find path " << endNode_.node_->pos.x << ", " << endNode_.node_->pos.y << std::endl;
    }

    astarsearch.EnsureMemoryFreed();
    instances.erase(instances.begin());
    finished_ = true;
}