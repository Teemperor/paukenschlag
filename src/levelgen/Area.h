#ifndef SHOOTER_AREA_H
#define SHOOTER_AREA_H


#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <string>

class Area {

public:

    Area() {
    }
    Area(int x, int y, int w, int h) : x_(x), y_(y), width_(w), height_(h) {
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

    int x() const {
        return x_;
    }

    int y() const {
        return y_;
    }

    int width() const {
        return width_;
    }

    int height() const {
        return height_;
    }

    int rightX() const {
        return x_ + width_;
    }

    int bottomY() const {
        return y_ + height_;
    }

    int biggestSize() {
        return std::max(width_, height_);
    }

    int smallestSize() {
        return std::min(width_, height_);
    }

    std::string& background() {
        return background_;
    }

private:

    int x_, y_, width_, height_;
    std::string background_;

};


#endif //SHOOTER_AREA_H
