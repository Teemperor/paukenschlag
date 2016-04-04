#include "AreaDistributor.h"

void AreaDistributor::splitAreas(Area& area) {

    // we split always when the current area is too big
    // or on a chance as long as we can split without going lower than the min size
    bool shouldSplit = area.biggestSize() > maxSize_
                       || (
                               area.smallestSize() > minSize_ * 2
                               && (rand() % 100 < 20)
                       );

    if (shouldSplit) {
        bool vertSplit;
        if (area.width() > minSize_ * 2) {
            if (area.height() > minSize_ * 2) {
                vertSplit = rand() % 2 == 0;
            } else {
                vertSplit = true;
            }
        } else {
            vertSplit = false;
        }

        Area area1, area2;

        if (vertSplit) {
            int newWidth = (rand() % (area.width() - 2 * minSize_)) + minSize_;

            area1 = Area(area.x(), area.y(), newWidth, area.height());
            area2 = Area(area.x() + newWidth, area.y(), area.width() - newWidth, area.height());
        } else {
            int newHeight = (rand() % (area.height() - 2 * minSize_)) + minSize_;

            area1 = Area(area.x(), area.y(), area.width(), newHeight);
            area2 = Area(area.x(), area.y() + newHeight, area.width(), area.height() - newHeight);
        }

        splitAreas(area1);
        splitAreas(area2);

    } else {
        areas_.push_back(area);
    }
}