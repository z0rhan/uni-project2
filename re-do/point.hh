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


    // Methods

    double distance(std::shared_ptr<Point>) const;

    int height_diff(std::shared_ptr<Point>) const;

    int x() const;

    int y() const;

    int height() const;

    std::string name() const;

    char marker() const;

private:

    // Attributes
    std::string name_;
    int x_, y_, height_;
    char marker_;
};

#endif // POINT_HH
