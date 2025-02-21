#include "route.hh"
#include "calculator.hh"

// Constructor
Route::Route() {
}

//---------------------------------------------------------------------
// Function to add a point to the route
// Takes two string paramaters, between which the route is to be added
void Route::enqueue(std::shared_ptr<Point> from, 
                    std::shared_ptr<Point> to) {
    // If the route is empty, set the head and tail to the given points
    if (!this->head_) {
        this->head_ = from;
        this->head_->next_ = to;
    } else {
        // otherwise, find 'from' in the route and set its next to 'to'
        std::shared_ptr<Point> temp = this->head_;
        
        while (temp != from && temp) {
            temp = temp->next_;
        }

        if (temp) {
            temp->next_ = to;
        } else {
            std::cerr << "Point not found in the route" << std::endl;
        }

    }
}

//----------------------------------------------------------------------
// Function to print the points in a route
void Route::print() const {
    std::shared_ptr<Point> temp = this->head_->next_;

    std::cout << this->head_->name_ << std::endl;

    while (temp) {
        std::cout << " -> "<< temp->name_ << std::endl;
        temp = temp->next_;
    }
}

//----------------------------------------------------------------------
// Function to calculate the length of a route
double Route::calculate_length() const {
    std::shared_ptr<Point> temp = this->head_;
    double length = 0.00;

    while (temp->next_) {
        length += distance(temp->x_, 
                           temp->y_, 
                           temp->next_->x_, 
                           temp->next_->y_);
    }

    return length;
}
