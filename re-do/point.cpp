#include "point.hh"

// Constructor
Point::Point(std::string name, 
             int x, int y, int height, 
             char marker)
{
    this->name_ = name;
    this->x_ = x;
    this->y_ = y;
    this->height_ = height;
    this->marker_ = marker;
}

//----------------------------------------------------------------------
//
double Point::distance(std::shared_ptr<Point> next_point) const
{
    return sqrt(pow(next_point->x_ - this->x_, 2) +
                pow(next_point->y_ - this->y_, 2));
}

//----------------------------------------------------------------------
//
int Point::height_diff(std::shared_ptr<Point> next_point) const
{
    return (next_point->height_ - this->height_);
}


//----------------------------------------------------------------------
// Getter functions
int Point::x() const {return this->x_;}
int Point::y() const {return this->y_;}
int Point::height() const {return this->height_;}
std::string Point::name() const {return this->name_;}
char Point::marker() const {return this->marker_;}

