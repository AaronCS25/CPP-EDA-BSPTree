#include "Line.h"

Line LineSegment::getLine() const {
    Point3D p;
    Vector3D v;

    p = this->getP1();
    v = Vector3D(this->getP2() - this->getP1()).unit();
    
    return Line(p, v);
}

bool Line::isParallel(const Line& l) const {
    // TODO: Implement isParallel(Line) function
    return false;
}

bool Line::isParallel(const Vector3D& v) const {
    // TODO: Implement isParallel(Vector3D) function
    return false;
}

bool Line::isParallel(const LineSegment& l) const {
    // TODO: Implement isParallel(LineSegment) function
    return false;
}

bool Line::isOrthogonal(const Line& l) const {
    // TODO: Implement isOrthogonal(Line) function
    return false;
}

bool Line::isOrthogonal(const Vector3D& v) const {
    // TODO: Implement isOrthogonal(Vector3D) function
    return false;
}

bool Line::isOrthogonal(const LineSegment& l) const {
    // TODO: Implement isOrthogonal(LineSegment) function
    return false;
}