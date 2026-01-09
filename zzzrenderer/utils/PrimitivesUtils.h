#ifndef RENDERER_UTILS_PRIMITIVESUTILS_H_
#define RENDERER_UTILS_PRIMITIVESUTILS_H_

#include "renderer/primitives/Point.h"
#include "renderer/primitives/Dimensions.h"

namespace PrimitivesUtils {
Point calculateCenter(Point origin, Dimensions dim);
bool isInRect(Point origin, Dimensions dim, Point query);
}
;

#endif /* RENDERER_UTILS_PRIMITIVESUTILS_H_ */
