#include "orienteeringmap.hh"
#include <iomanip>
#include <memory>
#include <string>

// Constructor
OrienteeringMap::OrienteeringMap() {
}

// Destructor
OrienteeringMap::~OrienteeringMap() {
}

//----------------------------------------------------------------------
// Set the size of the map
// Takes the height and width of the map as parameters
void OrienteeringMap::set_map_size(int width, int height) {
    this->height_ = height;
    this->width_ = width;
}

//----------------------------------------------------------------------
// Add pointers to the point in a map
// Key is the name of the point
// Value is the pointer to the point
void OrienteeringMap::add_point(std::string name,
                                int x, int y, int height,
                                char marker)
{
    std::shared_ptr<Point> control_point= std::make_shared<Point>();

    control_point->name_ = name;
    control_point->x_ = x;
    control_point->y_ = y;
    control_point->height_ = height;
    control_point->marker_ = marker;

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
    // Check if the control points exist
    if (this->control_points_.find(from) == this->control_points_.end() ||
        this->control_points_.find(to) == this->control_points_.end()) {
        return false;
    }

    // Check if the route already exists
    if (this->routes_.find(route_name) != this->routes_.end()) {
        this->routes_[route_name]->enqueue(this->control_points_.at(from),
                                           this->control_points_.at(to));
        return true;
    }

    // If the route does not exist, create a new route
    std::shared_ptr<Route> route = std::make_shared<Route>();

    route->enqueue(this->control_points_.at(from),
                   this->control_points_.at(to));

    this->routes_[route_name] = route;

    return true;
}

//----------------------------------------------------------------------
// Prints the layout of the map
// the co-ordinates are represented by a dot
// Also prints the control points on the map
void OrienteeringMap::print_map() const {
    std::map<std::pair<int, int>, std::shared_ptr<Point>> points_position;

    // map with postion to access the point when printing
    // we subtract 1 from x and y since we use 0 based indexing
    for (auto& [name, point]: this->control_points_) {
        points_position[{point->x_-1, point->y_-1}] = point;
    }

    // Print the x-axis at the top
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
                std::cout << std::setw(3) << it->second->marker_;
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
        std::cout << " - " << name << " : " << point->marker_ << std::endl;
    }
}

//----------------------------------------------------------------------
// Function to print the points in a route
// Takes the name of the route as a parameter
// If the route does not exist, print an error message
void OrienteeringMap::print_route(const std::string& route_name) const {
    // If the route does not exist
    if (this->routes_.find(route_name) == this->routes_.end()) {
        std::cout << "Error: Route named " 
                  << route_name 
                  << " can't be found" 
                  << std::endl;
        return;
    }

    // If the route exists, print
    this->routes_.at(route_name)->print();
    return;
}

//----------------------------------------------------------------------
// Function to print the length of a route
// Takes the name of the route as a parameter
void OrienteeringMap::route_length(const std::string& name) const {
    // If the route does not exist
    if (this->routes_.find(name) == this->routes_.end()) {
        std::cout << "Error: Route named " 
                  << name 
                  << " can't be found" 
                  << std::endl;
        return;
    }

    double route_length = this->routes_.at(name)->calculate_length();

    std::cout << std::setprecision(2) << "Route " 
                                      << name 
                                      << " length was "
                                      << route_length 
                                      << std::endl;

}

//----------------------------------------------------------------------
// Function that prints the greatest rise after a point
// along with the routes where the rise occurs
void OrienteeringMap::greatest_rise(const std::string& point_name) const {
    if (this->control_points_.find(point_name) ==
        this->control_points_.end())
    {
        std::cout << "Error: Point named "
                  << point_name
                  << " can't be found"
                  << std::endl;
        return;
    }

    std::shared_ptr<Point> point = this->control_points_.at(point_name);
    std::vector<std::pair<std::string, int>> greatest_rises;

    for (auto& [name, route]: this->routes_) {
        int rise = route->get_greatest_rise(point);

        if (rise > 0) {
            greatest_rises.push_back({name, rise});
        }
    }

    if (greatest_rises.empty()) {
        std::cout << "No route rises after point "
                  << point_name
                  << std::endl;
        return;
    }

    int max_rise = 0;
    std::vector<std::string> max_rise_routes;

    for (auto& pair: greatest_rises) {
        if (pair.second > max_rise) {
            max_rise = pair.second;
        }
    }

    for (auto& pair: greatest_rises) {
        if (pair.second == max_rise) {
            max_rise_routes.push_back(pair.first);
        }
    }


    std::cout << "Greatest rise after point "
              << point_name
              << ", "
              << max_rise
              << " meters, is on route(s):"
              << std::endl;

    for (auto& point: max_rise_routes) {
        std::cout << " - " << point << std::endl;
    }
}
