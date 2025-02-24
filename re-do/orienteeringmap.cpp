#include "orienteeringmap.hh"
#include <algorithm>
#include <memory>
#include <string>


// Constructor
OrienteeringMap::OrienteeringMap() {
}

// Destructor
OrienteeringMap::~OrienteeringMap() {
}

//----------------------------------------------------------------------
//
bool OrienteeringMap::route_exists(const std::string& name) const {
    return this->routes_.find(name) != this->routes_.end();
}

//----------------------------------------------------------------------
//
bool OrienteeringMap::point_exists(const std::string& name) const {
    return this->control_points_.find(name) != this->control_points_.end();
}

//----------------------------------------------------------------------
// Set the size of the map
// Takes the height and width of the map as parameters
void OrienteeringMap::set_map_size(int width, int height) {
    this->height_ = height;
    this->width_ = width;
}

//----------------------------------------------------------------------
// Add pointers to the point in a std::map
// Key is the name of the point
// Value is the pointer to the point
void OrienteeringMap::add_point(std::string name,
                                int x, int y, int height,
                                char marker)
{
    std::shared_ptr<Point> control_point = std::make_shared<Point>(
        Point(name, x, y, height, marker)
    );

    this->control_points_[name] = control_point;
}

//----------------------------------------------------------------------
// Function to connect two control points in a route
// Takes the names of the control points and the name of the route
// as parameters
// Returns true if the connection was successful and false otherwise
bool OrienteeringMap::connect_route(std::string from,
                                    std::string to,
                                    std::string route_name)
{
    if (!this->point_exists(from) || !this->point_exists(to)) {
        return false;
    }

    // If the route does not exist
    if (!this->route_exists(route_name)) {
        std::shared_ptr<Route> route = std::make_shared<Route>();

        route->enqueue(this->control_points_[from],
                       this->control_points_[to]);

        this->routes_[route_name] = route;

        return true;
    }

    // If the route exists
    std::shared_ptr<Route> route = this->routes_[route_name];

    route->enqueue(this->control_points_[from],
                   this->control_points_[to]);

    this->routes_[route_name] = route;

    return true;
}

//----------------------------------------------------------------------
// Prints the layout of the map with the control points
void OrienteeringMap::print_map() const {
    std::map<std::pair<int, int>, std::shared_ptr<Point>> points_position;

    for (auto& [name, point]: this->control_points_) {
        points_position[{point->x() - 1, point->y() - 1}] = point;
    }

    std::cout << " ";
    for (int i = 0; i < this->width_; i++) {
        std::cout << std::setw(3) << i+1;
    }
    std::cout << std::endl;


    for (int i = 0; i < this->height_; i++) {
        std::cout << std::setw(2) << i+1; 

        for (int j = 0; j < this->width_; j++) {
            auto it = points_position.find({j, i});

            if (it != points_position.end()) {
                std::cout << std::setw(3) << it->second->marker();
            } else {
                std::cout << std::setw(3) << "."; 
            }
        }
        std::cout << std::endl;
    }
}

//----------------------------------------------------------------------
// Function to print the list of all the routes
void OrienteeringMap::print_routes() const {
    std::cout << "Routes:" << std::endl;

    for (auto& [name, route]: this->routes_) {
        std::cout << " - "<< name << std::endl;
    }
}

//----------------------------------------------------------------------
// Function to print the points in the map
void OrienteeringMap::print_points() const {
    std::cout << "Points:" << std::endl;

    for (auto& [name, point]: this->control_points_) {
        std::cout << " - " << name << " : " << point->marker() << std::endl;
    }
}

//----------------------------------------------------------------------
// Function to print the points in a route
// Takes the name of the route as a parameter
// If the route does not exist, print an error message
void OrienteeringMap::print_route(const std::string& route_name) const {

    if (!this->route_exists(route_name)) {
        std::cout << "Error: Route named " 
                  << route_name 
                  << " can't be found" 
                  << std::endl;
        return;;
    }

    this->routes_.at(route_name)->print();
}

//----------------------------------------------------------------------
// Function to print the length of a route
// Takes the name of the route as a parameter
void OrienteeringMap::route_length(const std::string& name) const {

    if (!this->route_exists(name)) {
    std::cout << "Error: Route named " 
              << name 
              << " can't be found" 
              << std::endl;
    return;;
    }

    std::cout << "Route " << name << " length was " 
              << std::fixed << std::setprecision(1) 
              << this->routes_.at(name)->length() 
              << std::endl;
    
}

//----------------------------------------------------------------------
// Function that prints the greatest rise after a point
// along with the routes where the rise occurs
void OrienteeringMap::greatest_rise(const std::string& point_name) const {

    if (!this->point_exists(point_name)) {
        std::cout << "Error: Point named " 
                  << point_name 
                  << " can't be found" 
                  << std::endl;
        return;
    }

    std::shared_ptr<Point> point = this->control_points_.at(point_name);

    std::map<std::string, int> greatest_rises;

    for (auto& [name, route]: this->routes_) {
        int greatest_rise = route->greatest_rise(point);

        if (greatest_rise <= 0) {
            continue;
        }

        greatest_rises[name] = greatest_rise;
    }

    if (greatest_rises.empty()) {
        std::cout << "No route rises after point " 
                  << point_name 
                  << std::endl;
        return;
    }

    auto it = std::max_element(greatest_rises.begin(), 
                                    greatest_rises.end(),
                                    [](const std::pair<std::string, int> p1,
                                       const std::pair<std::string, int> p2)
                                    {return p1.second < p2.second;});

    int max_rise = it->second;

    std::cout << "Greatest rise after point " 
              << point_name 
              << ", " 
              << max_rise 
              << " meters, is on route(s):"
              << std::endl;

    for (auto& [name, rise]: greatest_rises) {
        if (rise == max_rise) {
            std::cout << " - " << name << std::endl;
        }
    }

}

