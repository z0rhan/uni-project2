#include "orienteeringmap.hh"

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
// Add pointers to the point in a std::map
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
    // To-do
    return true;
}

//----------------------------------------------------------------------
// Prints the layout of the map with the control points
void OrienteeringMap::print_map() const {
    std::map<std::pair<int, int>, std::shared_ptr<Point>> points_position;

    for (auto& [name, point]: this->control_points_) {
        points_position[{point->x_-1, point->y_-1}] = point;
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
    // To-do
}

//----------------------------------------------------------------------
// Function to print the length of a route
// Takes the name of the route as a parameter
void OrienteeringMap::route_length(const std::string& name) const {
    // To-do
}

//----------------------------------------------------------------------
// Function that prints the greatest rise after a point
// along with the routes where the rise occurs
void OrienteeringMap::greatest_rise(const std::string& point_name) const {
    // To-do
}

