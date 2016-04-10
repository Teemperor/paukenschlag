
#ifndef SHOOTER_ENEMYAI_H
#define SHOOTER_ENEMYAI_H

#include <list>

class Soldier;

class EnemyAI {

    std::list<Soldier*> guards_;

public:
    EnemyAI() {
    }
    
};

#endif //SHOOTER_ENEMYAI_H
