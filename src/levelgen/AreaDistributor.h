#ifndef SHOOTER_AREADISTRIBUTER_H
#define SHOOTER_AREADISTRIBUTER_H


#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>

#include "Area.h"
#include "LevelGenInfo.h"

class AreaDistributor {

public:

    AreaDistributor(LevelGenInfo& info, int x, int y, int w, int h) : info_(info) {
        baseArea_ = Area(x, y, w, h);
        splitAreas(baseArea_);
    }


private:

    void splitAreas(Area& area);

    Area baseArea_;
    LevelGenInfo& info_;

    const int minSize_ = 3;
    const int maxSize_ = 18;

};


#endif //SHOOTER_AREADISTRIBUTER_H
