#include "Line.h"

Line LineSegment::getLine() const {
    Point3D p;
    Vector3D v;

    p = this->getP1();
    v = Vector3D(this->getP2() - this->getP1()).unit();
    
    return Line(p, v);
}

bool LineSegment::intersects(LineSegment &l) const {
    Point3D p = this->getP1();
    Point3D q = l.getP1();

    Vector3D r = this->getP2() - this->getP1();
    Vector3D s = l.getP2() - l.getP1();

    Vector3D qp = q - p;
    
    Vector3D rxs = r.crossProduct(s);
    NType rxsNorm = rxs.mag();

    if (rxsNorm == 0) { return false; }

    NType t = qp.crossProduct(s).dotProduct(rxs) / rxsNorm;
    NType u = qp.crossProduct(r).dotProduct(rxs) / rxsNorm;

    if (t >= 0 && t <= 1 && u >= 0 && u <= 1) { return true; }

    return false;
}

Point3D LineSegment::getIntersectPoint(LineSegment &l) const {
    // TODO: Implement logic of getIntersectPoint
    return Point3D();
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