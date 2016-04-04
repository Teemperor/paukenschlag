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


    for (int i = 0; i < 3; i++)
        new Guard(level_, 180 + 80 * i, 180);

    new Hideaway(level_, 10 * SCALE, 10 * SCALE);
    AreaDistributor areaDistributor(10, 10, 100, 100);

    for (Area& area : areaDistributor.areas()) {
        level_.areas().push_back(LevelArea(area));

        if (area.width() > 3) {
            new Wall(level_,
                     b2Vec2(area.x(), area.y()),
                     b2Vec2(area.x() + 1, area.y()),
                     "data/walls/stone");
            new Door(level_, SCALE * (area.x() + 1), SCALE * area.y());
            new Wall(level_,
                     b2Vec2(area.x() + 3, area.y()),
                     b2Vec2(area.x() + area.width(), area.y()),
                     "data/walls/stone");
        } else {
            new Wall(level_,
                     b2Vec2(area.x(), area.y()),
                     b2Vec2(area.x() + area.width(), area.y()),
                     "data/walls/stone");
        }
        new Wall(level_,
                 b2Vec2(area.x() + area.width(), area.y()),
                 b2Vec2(area.x() + area.width(), area.y() + area.height()),
                 "data/walls/stone");
        new Wall(level_,
                 b2Vec2(area.x(), area.y()),
                 b2Vec2(area.x(), area.y() + area.height()),
                 "data/walls/stone");
        /*new Wall(level_,
                 b2Vec2(area.x(), area.y() + area.height()),
                 b2Vec2(area.x() + area.width(), area.y() + area.height()),
                 "data/walls/stone");*/
    }
}