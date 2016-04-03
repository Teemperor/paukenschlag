#ifndef SHOOTER_AREADISTRIBUTER_H
#define SHOOTER_AREADISTRIBUTER_H


#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>

class Area {

public:

    Area() {
    }
    Area(double x, double y, double w, double h) : x_(x), y_(y), width_(w), height_(h) {
        assert(h > 0.1);
        assert(w > 0.1);
    }

    bool overlap(const Area& other) {
        return (std::abs(this->x_ - other.x_) * 2 < (this->width_ + other.width_)) &&
               (std::abs(this->y_ - other.y_) * 2 < (this->height_ + other.height_));
    }

    bool contain(const Area& other) {
        return other.x_ > x_ && other.y_ > y_ && other.rightX() < rightX() && other.bottomY() < bottomY();
    }

    double x() const {
        return x_;
    }

    double y() const {
        return y_;
    }

    double width() const {
        return width_;
    }

    double height() const {
        return height_;
    }

    double rightX() const {
        return x_ + width_;
    }

    double bottomY() const {
        return y_ + height_;
    }

    double biggestSize() {
        return std::max(width_, height_);
    }

    double smallestSize() {
        return std::min(width_, height_);
    }

private:

    double x_, y_, width_, height_;

};

class AreaDistributor {

public:

    AreaDistributor(double w, double h) {
        baseArea_ = Area(0, 0, w, h);
        splitAreas(baseArea_);
    }


    std::vector<Area>& areas() {
        return areas_;
    }

private:

    void splitAreas(Area& area) {

        // we split always when the current area is too big
        // or on a chance as long as we can split without going lower than the min size
        bool shouldSplit = area.biggestSize() > maxSize_
                        || (
                            area.smallestSize() > minSize_ * 2
                            && (rand() % 100 < 70)
                        );

        if (shouldSplit) {
            bool vertSplit;
            if (area.width() >= minSize_ * 2) {
                if (area.height() >= minSize_ * 2) {
                    vertSplit = rand() % 2 == 0;
                } else {
                    vertSplit = true;
                }
            } else {
                vertSplit = false;
            }

            Area area1, area2;

            if (vertSplit) {
                double newWidth = ((rand() % 100) / 100.0) * area.width();
                newWidth = std::min(area.width() - minSize_, newWidth);
                newWidth = std::max(minSize_, newWidth);

                area1 = Area(area.x(), area.y(), newWidth, area.height());
                area2 = Area(area.x() + newWidth, area.y(), area.width() - newWidth, area.height());
            } else {
                double newHeight = ((rand() % 100) / 100.0) * area.height();
                newHeight = std::min(area.height() - minSize_, newHeight);
                newHeight = std::max(minSize_, newHeight);

                area1 = Area(area.x(), area.y(), area.width(), newHeight);
                area2 = Area(area.x(), area.y() + newHeight, area.width(), area.height() - newHeight);
            }

            splitAreas(area1);
            splitAreas(area2);

        } else {
            areas_.push_back(area);
        }
    }

    std::vector<Area> areas_;
    Area baseArea_;

    const double minSize_ = 4;
    const double maxSize_ = 20;

};


#endif //SHOOTER_AREADISTRIBUTER_H
