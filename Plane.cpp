#include "Plane.h"
#include <algorithm>

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
    if (this->distance(p) == 0) { return true; }
    return false;
}

bool Plane::contains(const Line &l) const {
    if (!this->intersects(l) && this->contains(l.getPoint())) { return true; }
    return false;
}

Plane Polygon::getPlane() const {
    Point3D p = vertices[0];
    Vector3D normal = getNormal();

    return Plane(p, normal);
}

Vector3D Polygon::getNormal() const {
    // TODO: Manejar colinealidad de puntos
    Point3D p0 = vertices[0];
    Point3D p1 = vertices[1];
    Point3D p2 = vertices[2];

    Vector3D v0 = p1 - p0;
    Vector3D v1 = p2 - p0;

    Vector3D normal = v0.crossProduct(v1);

    if (normal.mag() == 0) {
        throw std::runtime_error("Los puntos proporcionados son colineales.");
    }

    return normal.unit();
}

Point3D Polygon::getCentroid() const {
    // TODO: Implement getCentroid function
    return Point3D();
}

bool Polygon::contains(const Point3D &p) const {
    if (!this->getPlane().contains(p)) { return false; }

    Point3D p1 = vertices[0];
    Point3D p2 = vertices[1];
    Point3D midpoint = (p1 + p2) / 2;

    Vector3D direction = Vector3D(midpoint - p).unit();

    Point3D min = vertices[0], max = vertices[0];
    for (const auto& v : vertices) {
        min = Point3D(std::min(min.getX(), v.getX()), std::min(min.getY(), v.getY()), std::min(min.getZ(), v.getZ()));
        max = Point3D(std::max(max.getX(), v.getX()), std::max(max.getY(), v.getY()), std::max(max.getZ(), v.getZ()));
    }

    if (p.getX() < min.getX() || p.getX() > max.getX() ||
        p.getY() < min.getY() || p.getY() > max.getY() ||
        p.getZ() < min.getZ() || p.getZ() > max.getZ()) {
        return false;
    }

    NType boundingBoxDiagonal = min.distance(max);
    Point3D extendedPoint = p + (direction * boundingBoxDiagonal);

    LineSegment ray(p, extendedPoint);

    int intersections = 0;
    for (size_t i = 0; i < vertices.size(); ++i) {
        Point3D a = vertices[i];
        Point3D b = vertices[(i + 1) % vertices.size()];
        LineSegment edge(a, b);

        if (a == p || b == p) { return true; }
        // if (edge.contains(p)) { return true; }

        if (ray.intersects(edge)) {
            if (p == a || p == b) {
                Point3D prev = vertices[(i - 1 + vertices.size()) % vertices.size()];
                Point3D next = vertices[(i + 2) % vertices.size()];

                if ((prev.getY() > p.getY() && next.getY() > p.getY()) ||
                    (prev.getY() < p.getY() && next.getY() < p.getY())) {
                    continue;
                }
            }
            intersections++;
        }
    }

    return (intersections % 2 == 1);
}

RelationType Polygon::relationWithPlane(const Plane &plane) const {
    // TODO: Implement relationWithPlane function
    return RelationType::COINCIDENT;
}

std::pair<Polygon, Polygon> Polygon::split(const Plane &plane) const {
    std::vector<Point3D> frontVertices;
    std::vector<Point3D> backVertices;

    // !Only support convex polygons

    if (this->getPlane() == plane) {
        throw std::runtime_error("The plane is the same as the polygon's plane.");
    }

    for (size_t i = 0; i < this->vertices.size(); i++)
    {
        NType currentDistance = plane.distance(this->vertices[i]);
        NType nextDistance = plane.distance(this->vertices[(i + 1) % this->vertices.size()]);

        if (currentDistance > 0) { frontVertices.push_back(this->vertices[i]);}
        else if (currentDistance < 0) { backVertices.push_back(this->vertices[i]); }
        else {
            frontVertices.push_back(this->vertices[i]);
            backVertices.push_back(this->vertices[i]);
            continue;
        }
        
        if (currentDistance > 0 && nextDistance < 0 || currentDistance < 0 && nextDistance > 0)
        {
            Point3D intersectionPoint = plane.getIntersectPoint(LineSegment(this->vertices[i], this->vertices[(i + 1) % this->vertices.size()]).getLine());
            frontVertices.push_back(intersectionPoint);
            backVertices.push_back(intersectionPoint);
        }
    }

    return std::make_pair(Polygon(frontVertices), Polygon(backVertices));
}

NType Polygon::area() const {
    // TODO: Implement area function
    return 0;
}

bool Plane::operator==(const Plane &other) const {
    Vector3D n1 = this->_n.unit();
    Vector3D n2 = other._n.unit();

    if ((n1 == n2 || n1 == -n2) && this->contains(other._p)) { return true; }

    return false;
}

bool Plane::operator!=(const Plane &other) const {
    return !(*this == other);
}

bool Polygon::operator==(const Polygon &other) const {
    size_t vertexSize1 = this->vertices.size();
    size_t vertexSize2 = other.vertices.size();

    if (vertexSize1 != vertexSize2) { return false; }

    Point3D startPoint = this->vertices[0];
    auto it = std::find(other.vertices.begin(), other.vertices.end(), startPoint);

    if (it == other.vertices.end()) { return false; }

    size_t startIdx = std::distance(other.vertices.begin(), it);

    for (size_t i = 0; i < vertexSize1; ++i) {
        if (this->vertices[i] != other.vertices[(startIdx + i) % vertexSize2]) {
            return false;
        }
    }
    
    return true;
}

bool Polygon::operator!=(const Polygon &other) const {
    return !(*this==other);
}