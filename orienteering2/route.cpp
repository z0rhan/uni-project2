#include "route.hh"
#include <memory>

// Constructor
Route::Route() : head_(nullptr) {}

//---------------------------------------------------------------------
// Function to add a point to the route
// Takes two string paramaters, between which the route is to be added
void Route::enqueue(std::shared_ptr<Point> from, 
                    std::shared_ptr<Point> to) {
    // If the route is empty, set the head and tail to the given points
    if (!this->head_) {
        std::shared_ptr<Node> node_from = std::make_shared<Node>();
        node_from->point_ = from;
        this->head_ = node_from;

        std::shared_ptr<Node> node_to = std::make_shared<Node>();
        node_to->point_ = to;
        this->head_->next_ = node_to;

    } else {
        // otherwise, find 'from' in the route and set its next to 'to'
        std::shared_ptr<Node> temp = this->head_;
        
        while (temp && temp->point_ != from) {
            temp = temp->next_;
        }

        if (temp) {
            std::shared_ptr<Node> node_to = std::make_shared<Node>();
            node_to->point_ = to;
            temp->next_ = node_to;
        } 
    }
}

//----------------------------------------------------------------------
// Function to print the points in a route
void Route::print() const {
    std::shared_ptr<Node> temp = this->head_->next_;

    std::cout << this->head_->point_->name_ << std::endl;

    while (temp) {
        std::cout << " -> "<< temp->point_->name_ << std::endl;
        temp = temp->next_;
    }
}

//----------------------------------------------------------------------
// Function to calculate the length of a route
// Returns the length of the current route
double Route::calculate_length() const {
    std::shared_ptr<Node> temp = this->head_;
    double length = 0.00;

    while (temp->next_) {
        length += this->get_distance(temp->point_,
                                     temp->next_->point_);
        temp = temp->next_;
    }

    return length;
}

// Function to calculate the distance between two points
// Takes two shared pointers to points as parameters
// Returns the distance between the points
double Route::get_distance(std::shared_ptr<Point> p1,
                        std::shared_ptr<Point> p2) const {
    double dx = p1->x_ - p2->x_;
    double dy = p1->y_ - p2->y_;

    return sqrt(dx*dx + dy*dy);
}

//----------------------------------------------------------------------
// Function to calculate the greatest rise in a route from a given point
// Takes a shared pointer to a point as a parameter
// Returns the greatest rise from the given point
int Route::get_greatest_rise(std::shared_ptr<Point> point) const {
    // Route is empty
    if (!this->head_) {
        std::cout << "Error: Route is empty" << std::endl;
        return -1;
    }

    std::shared_ptr<Node> temp = this->head_;

    while (temp && temp->point_ != point) {
        temp = temp->next_;
    }
    
    // Point does not exist in the route
    if (!temp) {
        return -1;
    }

    int greatest_rise = 0;
    int temp_rise = 0;

    while (temp->next_) {
        temp_rise = this->get_height_difference(point,
                                                temp->next_->point_);

        if (temp_rise > greatest_rise) {
            greatest_rise = temp_rise;
        }

        temp = temp->next_;
    }

    return greatest_rise;
}

//----------------------------------------------------------------------
// Function to calculate the height difference between two points
// Takes two shared pointers to points as parameters
// Returns the height difference between the points
int Route::get_height_difference(std::shared_ptr<Point> p1,
                                std::shared_ptr<Point> p2) const
{
    return (p2->height_ - p1->height_);
}
