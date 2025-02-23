#ifndef POINT_HH
#define POINT_HH

#include <string>

class Point {
public:
    // Constructor
    Point();

    // Attributes
    std::string name_;
    int x_, y_, height_;
    char marker_;

    // Methods

    double distance() const;

    int height_diff() const;

private:

};

#endif // POINT_HH
