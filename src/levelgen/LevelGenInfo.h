#ifndef SHOOTER_LEVELGENINFO_H
#define SHOOTER_LEVELGENINFO_H

#include "Area.h"

class LevelGenInfo {

public:
    LevelGenInfo() {
    }

    std::vector<Area>& areas() {
        return areas_;
    }

private:

    std::vector<Area> areas_;
};


#endif //SHOOTER_LEVELGENINFO_H
