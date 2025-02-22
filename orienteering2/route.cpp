#include "route.hh"

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
double Route::calculate_length() const {
    std::shared_ptr<Node> temp = this->head_;
    double length = 0.00;

    while (temp->next_) {
        length += this->distance(temp->point_, temp->next_->point_);
        temp = temp->next_;
    }

    return length;
}

// Function to calculate the distance between two points
// Takes two shared pointers to points as parameters
// Returns the distance between the points
double Route::distance(std::shared_ptr<Point> p1, 
                        std::shared_ptr<Point> p2) const {
    double dx = p1->x_ - p2->x_;
    double dy = p1->y_ - p2->y_;

    return sqrt(dx*dx + dy*dy);
}
