#include "calculator.hh"
#include <cmath>

// Function to calculate the distance between two points
// Takes the x and y coordinates of the two points as parameters
// Returns the distance between the points
double distance(double x, double y, double x1, double y1) {
    return sqrt(pow(x1 - x, 2) + pow(y1 - y, 2));
}

