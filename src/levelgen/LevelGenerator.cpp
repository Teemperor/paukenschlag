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

    new Cover(level_, 300, 600);

    for (int i = 0; i < 10; i++)
        new Crate(level_, 2000, 2000);

    new Hideaway(level_, 0, 0);
    new EscapeArea(level_, 350, 150);

    new Door(level_, 64, 64);

    //for (int i = 0; i < 3; i++)
    //    new Guard(level_, 1080 + 80 * i, 1000);

    new Hideaway(level_, 10 * SCALE, 10 * SCALE);
    AreaDistributor areaDistributor(100, 100);

    for (Area& area : areaDistributor.areas()) {
        level_.areas().push_back(LevelArea(area));
        new Wall(level_,
                 b2Vec2(area.x(), area.y()),
                 b2Vec2(area.x() + area.width(), area.y()),
                 10, "data/walls/stone");
        new Wall(level_,
                 b2Vec2(area.x() + area.width(), area.y()),
                 b2Vec2(area.x() + area.width(), area.y() + area.height()),
                 10, "data/walls/stone");
        new Wall(level_,
                 b2Vec2(area.x(), area.y()),
                 b2Vec2(area.x(), area.y() + area.height()),
                 10, "data/walls/stone");
    }
}