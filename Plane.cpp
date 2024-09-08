#include "Plane.h"

NType Plane::distance(const Point3D &p) const {
    NType a = _n.getX(), b = _n.getY(), c = _n.getZ();
    NType x0 = _p.getX(), y0 = _p.getY(), z0 = _p.getZ();

    NType x = p.getX(), y = p.getY(), z = p.getZ();

    return (a*(x-x0) + b*(y-y0) + c*(z-z0)) / sqrt(a*a + b*b + c*c) ;
}

Point3D Plane::intersect(const Line &l) const {
    // TODO: Implement intersect function
    return Point3D();
}

bool Plane::contains(const Point3D &p) const {
    // TODO: Implement contains(Point3D) function
    return false;
}

bool Plane::contains(const Line &l) const {
    // TODO: Implement contains(Line) function
    return false;
}

Plane Polygon::getPlane() const {
    // TODO: Implement getPlane function
    return Plane(Point3D(), Vector3D());
}

Point3D Polygon::getNormal() const {
    // TODO: Implement getNormal function
    return Point3D();
}

Point3D Polygon::getCentroid() const {
    // TODO: Implement getCentroid function
    return Point3D();
}

bool Polygon::contains(const Point3D &p) const {
    // TODO: Implement contains function
    return false;
}

RelationType Polygon::relationWithPlane(const Plane &plane) const {
    // TODO: Implement relationWithPlane function
    return RelationType::COINCIDENT;
}

std::pair<Polygon, Polygon> Polygon::split(const Plane &plane) const {
    // TODO: Implement split function
    return std::make_pair(Polygon(std::vector<Point3D>()), Polygon(std::vector<Point3D>()));
}

NType Polygon::area() const {
    // TODO: Implement area function
    return 0;
}

bool Plane::operator==(const Plane &other) const {
    // TODO: Implement the == operador
    return false;
}

bool Plane::operator!=(const Plane &other) const {
    // TODO: Implement the != operador
    return false;
}

bool Polygon::operator==(const Polygon &other) const {
    // TODO: Implement the == operador
    return false;
}

bool Polygon::operator!=(const Polygon &other) const {
    // TODO: Implement the != operador
    return false;
}