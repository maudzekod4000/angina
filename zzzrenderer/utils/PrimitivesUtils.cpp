#include "PrimitivesUtils.h"

#include <utility>
#include <iostream>

#include "core/math/geometry/Geometry.h"

Point PrimitivesUtils::calculateCenter(Point origin, Dimensions dim) {
	PointPair originPair = std::make_pair(origin.x, origin.y);
	DimensionsPair dimPair = std::make_pair(dim.w, dim.w);
	PointPair center = Geometry::calculateCenter(originPair, dimPair);

	return {center.first, center.second};
}

bool PrimitivesUtils::isInRect(Point origin, Dimensions dim, Point query) {
	PointPair originPair = std::make_pair(origin.x, origin.y);
	DimensionsPair dimPair = std::make_pair(dim.w, dim.h);
	PointPair queryPair = std::make_pair(query.x, query.y);

	bool res = Geometry::isInRect(originPair, dimPair, queryPair);

	return res;
}
