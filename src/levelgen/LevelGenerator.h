#ifndef SHOOTER_LEVELGENERATOR_H
#define SHOOTER_LEVELGENERATOR_H

#include "LevelGenInfo.h"

class Level;

class LevelGenerator {



public:

    LevelGenerator(Level& level) : level_(level) {
    }

    void generate();



private:

    Level& level_;
    LevelGenInfo info;

};


#endif //SHOOTER_LEVELGENERATOR_H
