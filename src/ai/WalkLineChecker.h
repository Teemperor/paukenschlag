

#ifndef SHOOTER_WALKLINECHECKER_H
#define SHOOTER_WALKLINECHECKER_H


#include <Box2D/Dynamics/b2WorldCallbacks.h>

class Level;

class WalkLineChecker : public b2RayCastCallback {

    bool lineIsFree_ = true;

public:
    static bool isFree(Level& level, b2Vec2& start, b2Vec2& end);

    virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                  const b2Vec2& normal, float32 fraction);
};


#endif //SHOOTER_WALKLINECHECKER_H
