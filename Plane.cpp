#include "Plane.h"

NType Plane::distance(const Point3D &p) const {
    Point3D r0 = this->_p;
    Vector3D n = this->_n.unit();

    return n.dotProduct(p - r0);
}

bool Plane::intersects(const Line &l) const {
    Vector3D n = this->_n;
    Vector3D v = l.getUnit();

    if (n.dotProduct(v) != 0) { return true; }

    return false;
}

Point3D Plane::getIntersectPoint(const Line &l) const {
    Vector3D n = this->_n;
    Point3D r0 = _p;

    Point3D P = l.getPoint();
    Vector3D v = l.getUnit();

    NType numerator = n.dotProduct(P-r0);
    NType denominator = n.dotProduct(v);

    if (denominator == 0) {
        throw std::runtime_error("La línea es paralela al plano y no intersecta.");
    }

    NType t = numerator / denominator;
    Point3D iPoint = P + v * t;
    
    return iPoint;
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