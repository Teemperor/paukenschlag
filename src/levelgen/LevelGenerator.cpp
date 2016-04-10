#include "LevelGenerator.h"
#include "LevelArea.h"
#include "Level.h"
#include <Character.h>
#include <Cover.h>
#include <Crate.h>
#include <Hideaway.h>
#include <goals/EscapeArea.h>
#include <guard/Soldier.h>
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
        new Soldier(level_, 180 + 80 * i, 180);

    new Hideaway(level_, 10 * SCALE, 10 * SCALE);

    AreaDistributor(info, 10, 10, 100, 100);

    Area grass1(0, 0, 10, 100);
    Area grass2(10, 0, 100, 10);
    grass1.background() = "grass";
    grass2.background() = "grass";
    info.areas().push_back(grass1);
    info.areas().push_back(grass2);

    for (Area& area : info.areas()) {
        level_.areas().push_back(LevelArea(area));

        if (area.background() == "grass")
            continue;
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