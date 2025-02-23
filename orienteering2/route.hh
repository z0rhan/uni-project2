#ifndef ROUTE_HH
#define ROUTE_HH

#include <memory>
#include <string>
#include <iostream>
#include <cmath>

// Data structure for a point in the map
//----------------------------------------------------------------------------
// The point has a name, position (x and y coordinates),
// height and a marker.
struct Point
{
    std::string name_;
    int x_, y_, height_;
    char marker_;
};


class Route {
public:
    // Constructor
    Route();

    // Takes two pointers to 'Point' struct and connects them
    void enqueue(std::shared_ptr<Point> from,
                 std::shared_ptr<Point> to);

    // Prints the points in the route
    void print() const;

    // Calculates the length of the route
    double calculate_length() const;

    // Calculates the distance between two points
    double get_distance(std::shared_ptr<Point>,
                        std::shared_ptr<Point>) const;

    // Calculate greatest rise
    int get_greatest_rise(std::shared_ptr<Point>) const;

    // Calculate height difference between two points
    int get_height_difference(std::shared_ptr<Point>,
                              std::shared_ptr<Point>) const;

private:
    // Node struct for the linked list
    // Contains a pointer to a 'Point' struct
    // and a pointer to the next node
    struct Node {
        std::shared_ptr<Point> point_;
        std::shared_ptr<Node> next_;
    };

    // Pointer to the first node in the linked list
    std::shared_ptr<Node> head_;

};



#endif // ROUTE_HH
