#include "CollisionDetector.h"

#include <vector>

#include "enginev2/models/GameObject.h"
#include "enginev2/collisions/BoundingBox.h"
#include "enginev2/graphics/models/Line.h"
#include "enginev2/graphics/models/Point.h"

std::vector<CollisionData> CollisionDetector::detectCollisions(const std::vector<GameObject>& gameObjects)
{
	std::vector<CollisionData> collidedObjects;

	for (const GameObject& first : gameObjects) {
		// Create segments from the first bounding box.
		std::vector<Line> segments;
		Point upLeft(first.box.min.x, first.box.max.y);
		Point upRight(first.box.max);
		Point downRight(first.box.max.x, first.box.min.y);
		Point downLeft(first.box.min);

		// We will have all the normals in standard coordinates (x increases to the right and y increases to the top)
		// before outputting any coordinates to the screen we have to do a conversion.

		// We assign the points to the segments in specific order, so we can map a line to a bounding box with thickness of 0.
		segments.push_back(Line(upLeft, upRight, Point(0, 1))); // top segment
		segments.push_back(Line(downRight, upRight, Point(1, 0))); // right segment
		segments.push_back(Line(downLeft, downRight, Point(0, -1))); // bottom segment
		segments.push_back(Line(downLeft, upLeft, Point(-1, 0))); // left segment

		for (const GameObject& second : gameObjects) {
			if (first.id != second.id) {
				for (Line& seg : segments) {
					if (second.box.intersects(seg)) {
						collidedObjects.push_back(CollisionData{ first, second, seg.N });
					}
				}
			}
		}
	}

	return collidedObjects;
}
