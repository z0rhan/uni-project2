#ifndef ROUTE_HH
#define ROUTE_HH

#include <memory>
#include <string>
#include <iostream>
#include <cmath>

#include "point.hh"

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
    double length() const;

    // Calculate greatest rise
    int greatest_rise(std::shared_ptr<Point>) const;

    // Calculate height difference between two points
    int height_difference(std::shared_ptr<Point>,
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

#endif // !ROUTE_HH
