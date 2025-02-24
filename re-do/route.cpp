#include "route.hh"

// Constructor
Route::Route() : head_(nullptr) {}

//---------------------------------------------------------------------
// Function to add a point to the route
// Takes two string paramaters, between which the route is to be added
void Route::enqueue(std::shared_ptr<Point> from, 
                    std::shared_ptr<Point> to) {
    // If the route is empty
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

    std::cout << this->head_->point_->name() << std::endl;

    while (temp) {
        std::cout << " -> "<< temp->point_->name() << std::endl;
        temp = temp->next_;
    }
}

//----------------------------------------------------------------------
// Function to calculate the length of a route
// Returns the length of the current route
double Route::length() const {
    std::shared_ptr<Node> temp = this->head_;
    double length = 0.00;

    while (temp->next_) {
        length += temp->point_->distance(temp->next_->point_);
        temp = temp->next_;
    }

    return length;
}

//----------------------------------------------------------------------
// Function to calculate the greatest rise in a route from a given point
// Takes a shared pointer to a point as a parameter
// Returns the greatest rise from the given point
int Route::greatest_rise(std::shared_ptr<Point> point) const {
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

    // Point is the last point in the route
    if (!temp->next_) {
        return 0;
    }

    int greatest_rise = 0;
    int current_height = temp->point_->height();

    while (temp->next_) {
        int next_height = temp->next_->point_->height();
        int temp_rise = next_height - current_height;

        if (temp_rise > greatest_rise) {
            greatest_rise = temp_rise;
        }

        temp = temp->next_;
    }

    return greatest_rise;
}


