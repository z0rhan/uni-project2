#ifndef ROUTE_HH
#define ROUTE_HH

#include <memory>
#include <string>
#include <iostream>

// Data structure for a point in the map
//----------------------------------------------------------------------------
// The point has a name, position (x and y coordinates),
// height and a marker. Also has a pointer to implement a linked list.
struct Point
{
    std::string name_;
    int x_, y_, height_;
    char marker_;
    std::shared_ptr<Point> next_;
};

class Route {
public:
    // Constructor
    Route();

    // Takes two pointers to 'Point' struct and connects them
    void enqueue(std::shared_ptr<Point> from,std::shared_ptr<Point> to);

    // Prints the points in the route
    void print() const;

    // Calculates the length of the route
    double calculate_length() const;

private:
    std::shared_ptr<Point> head_;
    std::shared_ptr<Point> tail_;

};



#endif // ROUTE_HH
