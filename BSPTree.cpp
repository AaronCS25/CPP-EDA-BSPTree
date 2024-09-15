#include "BSPTree.h"

void BSPNode::insert(const Polygon &polygon) {
    if (polygon.relationWithPlane(partition) == RelationType::COINCIDENT) {
        polygons.push_back(polygon);
        return;
    }

    if (polygon.relationWithPlane(partition) == RelationType::IN_FRONT) {
        if (!front) {
            front = new BSPNode(polygon.getPlane());
        }
        front->insert(polygon);
        return;
    }

    if (polygon.relationWithPlane(partition) == RelationType::BEHIND) {
        if (!back) {
            back = new BSPNode(polygon.getPlane());
        }
        back->insert(polygon);
        return;
    }

    if (polygon.relationWithPlane(partition) == RelationType::SPLIT) {
        std::pair<Polygon, Polygon> splitPolygons = polygon.split(partition);
        if (!front) {
            front = new BSPNode(splitPolygons.first.getPlane());
        }
        if (!back) {
            back = new BSPNode(splitPolygons.second.getPlane());
        }
        front->insert(splitPolygons.first);
        back->insert(splitPolygons.second);
    }

    return;
}

const Polygon* BSPNode::detectCollision(const LineSegment& traceLine) const {
    // TODO: Implement the detectCollision logic
    return nullptr;
}

void BSPTree::insert(const Polygon &polygon) {
    if (!root) {
        root = new BSPNode(polygon.getPlane());
    }
    root->insert(polygon);
    return;
}