#include "Line.h"

Line LineSegment::getLine() const {
    Point3D p;
    Vector3D v;

    p = this->getP1();
    v = Vector3D(this->getP2() - this->getP1()).unit();
    
    return Line(p, v);
}

bool Line::isParallel(const Line& l) const {
    Vector3D v1 = this->getUnit();
    Vector3D v2 = l.getUnit();

    if (v1 == v2 || v1 == -v2) { return true; }

    return false;
}

bool Line::isParallel(const Vector3D& v) const {

    Vector3D v1 = this->getUnit();
    Vector3D v2 = v.unit();

    if (v1 == v2 || v1 == -v2) { return true; }

    return false;
}

bool Line::isParallel(const LineSegment& l) const {
    Vector3D v1 = this->getUnit();
    Vector3D v2 = Vector3D(l.getP2() - l.getP1()).unit();

    if (v1 == v2 || v1 == -v2) { return true; }

    return false;
}

bool Line::isOrthogonal(const Vector3D& v) const {
    Vector3D v1 = this->v;

    if (v1.dotProduct(v) == 0) { return true; }

    return false;
}

bool Line::isOrthogonal(const Line& l) const {
    return isOrthogonal(l.v);
}

bool Line::isOrthogonal(const LineSegment& l) const {
    return isOrthogonal(l.getLine());
}