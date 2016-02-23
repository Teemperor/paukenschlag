

#ifndef SHOOTER_NAVGRID_H
#define SHOOTER_NAVGRID_H

#include <cstdint>
#include <vector>
#include <Box2D/Dynamics/b2Body.h>
#include <Constants.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <GameObject.h>
#include <algorithm>
#include <chrono>
#include <Utils.h>
#include "WalkLineChecker.h"
#include <iostream>

class Level;
class AStarPath;

class NavNode {
    std::vector<NavNode*> neighbours_;
public:
    b2Vec2 pos;

    NavNode() {
    }
    NavNode(float x, float y) : pos(x, y) {
    }

    void addNeighbour(NavNode *neighbour) {
        if (std::find(neighbours_.begin(), neighbours_.end(), neighbour) == neighbours_.end()) {
            neighbours_.push_back(neighbour);
            neighbour->addNeighbour(this);
        }
    }

    const std::vector<NavNode*> neighbours() const {
        return neighbours_;
    }
};

class NavGrid {

    std::vector<std::vector<NavNode*>> nodes_;

    float gridSpacing_ = 1;
    float xMax_ = 50;
    float yMax_ = 50;

    Level* level_;

public:
    NavGrid() {
    }

    ~NavGrid() {
    }

    AStarPath* searchPath(b2Vec2& start, b2Vec2& end);

    void clear() {
        for(std::vector<NavNode*>& nodeList : nodes_) {
            for(NavNode* node : nodeList) {
                delete node;
            }
        }
        nodes_.clear();
    }

    void setLevel(Level* level) {
        clear();
        for (float x = gridSpacing_ / 2; x < xMax_; x += gridSpacing_) {
            nodes_.push_back(std::vector<NavNode*>());
            for (float y = gridSpacing_ / 2; y < yMax_; y += gridSpacing_) {
                addNode(new NavNode(x, y));
            }
        }

        for(std::vector<NavNode*>& nodeList : nodes_) {
            for(NavNode* node : nodeList) {
                for(std::vector<NavNode*>& nodeList2 : nodes_) {
                    for(NavNode* node2 : nodeList2) {
                        if (node == node2)
                            continue;
                        double distance = Utils::distance(node->pos, node2->pos);
                        if (Utils::distance(node->pos, node2->pos) <= gridSpacing_ * 1.5) {
                            if (WalkLineChecker::isFree(*level, node->pos, node2->pos)
                                    && WalkLineChecker::isFree(*level, node2->pos, node->pos)) {
                                node->addNeighbour(node2);
                            } else {
                                std::cout << "NOT FREE" << std::endl;
                            }
                        }
                    }
                }
            }
        }
    }

    void addNode(NavNode* node) {
        unsigned x = (unsigned int) (node->pos.x / gridSpacing_);
        unsigned y = (unsigned int) (node->pos.y / gridSpacing_);
        if (x >= nodes_.size())
            nodes_.resize(x + 1);
        if (y >= nodes_[x].size())
            nodes_[x].resize(y + 1);
        nodes_[x][y] = node;
    }
};


#endif //SHOOTER_NAVGRID_H
