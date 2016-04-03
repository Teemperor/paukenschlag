#include "LevelGenerator.h"
#include "LevelArea.h"
#include "Level.h"
#include <Character.h>
#include <Cover.h>
#include <Crate.h>
#include <Hideaway.h>
#include <goals/EscapeArea.h>
#include <guard/Guard.h>
#include <Door.h>
#include <levelgen/LevelGenerator.h>
#include <levelgen/AreaDistributor.h>

void LevelGenerator::generate() {

    for (int i = 0; i < 10; i++) {
        int x = Utils::rndGen() % 2000;
        int y = Utils::rndGen() % 2000;
        float length = Utils::rndGen() % 200 + 30;
        new Wall(level_, x, y, length, "");
    }

    new Cover(level_, 300, 600);

    for (int i = 0; i < 10; i++)
        new Crate(level_, 2000, 2000);

    new Hideaway(level_, 0, 0);
    new EscapeArea(level_, 350, 150);

    new Door(level_, 140, 100);

    for (int i = 0; i < 3; i++)
        new Guard(level_, 1080 + 80 * i, 1000);

    new Hideaway(level_, 10 * SCALE, 10 * SCALE);
    AreaDistributor areaDistributor(10, 10);

    for (Area& area : areaDistributor.areas()) {
        level_.areas().push_back(LevelArea(area));
    }
}