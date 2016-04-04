
#include "WalkLineChecker.h"
#include <Level.h>

const std::vector<float> checkOffsets = {-0.3f, 0, 0.3f};

bool WalkLineChecker::isFree(Level& level, b2Vec2& start, b2Vec2& end) {
    for (float xOffset : checkOffsets) {
        for (float yOffset : checkOffsets) {
            b2Vec2 currentStart = {start.x + xOffset, start.y + yOffset};
            b2Vec2 currentEnd = {end.x + xOffset, end.y + yOffset};
            WalkLineChecker checker;
            level.world().RayCast(&checker, currentStart, currentEnd);
            if (!checker.lineIsFree_) {
                return false;
            }
        }
    }
    return true;
}

float32 WalkLineChecker::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                               const b2Vec2& normal, float32 fraction) {

    GameObject* object = static_cast<GameObject*>(fixture->GetUserData());


    if (object->isObstacle()) {
        lineIsFree_ = false;
        return 0;
    }

    return -1;
}