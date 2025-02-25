#ifndef POINT_HH
#define POINT_HH

#include <memory>
#include <string>
#include <cmath>

class Point {
public:
    // Constructor
    Point(std::string name,
          int x, int y, int height, 
          char marker);

    // Calculate the distance between two points
    double distance(std::shared_ptr<Point>) const;

    // Getters
    std::string name() const; // name
    int x() const; // x coordinate
    int y() const; // y coordinate
    int height() const; // height
    char marker() const; // marker

private:

    // Attributes
    std::string name_;
    int x_, y_, height_;
    char marker_;
};

#endif // POINT_HH
