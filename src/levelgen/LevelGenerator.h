#ifndef SHOOTER_LEVELGENERATOR_H
#define SHOOTER_LEVELGENERATOR_H

class Level;

class LevelGenerator {

public:

    LevelGenerator(Level& level) : level_(level){
    }

    void generate();

private:

    Level& level_;

};


#endif //SHOOTER_LEVELGENERATOR_H
