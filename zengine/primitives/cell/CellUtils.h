#ifndef CHESS_GAME_BOARD_CELLUTILS_H_
#define CHESS_GAME_BOARD_CELLUTILS_H_

#include <string>

#include "renderer/primitives/Point.h"
#include "renderer/primitives/Dimensions.h"

#include "engine/primitives/cell/Cell.h"

namespace CellUtils {

inline Point cellToPoint(Cell cell, Dimensions cellDimensions, Point offset =
		Point::ZERO) {
	return Point { cell.col * cellDimensions.w, cell.row * cellDimensions.h }
			+ offset;
}

inline Cell pointToCell(Point point, Dimensions cellDimensions, Point offset =
		Point::ZERO) {
	Point cellOriginPoint = point - offset;
	return {cellOriginPoint.y / cellDimensions.h, cellOriginPoint.x / cellDimensions.w};
}

/*
 * Translates the cells that use top-left as 0,0 to chess coordinates which are from A-H for columns and
 * 1-8 (top to bottom row) for rows.
 */
inline std::string toChessCoordinates(const Cell &cell) {
	return std::string() + static_cast<char>(65 + cell.col)
			+ static_cast<char>(56 - cell.row);
}

}

#endif /* CHESS_GAME_BOARD_CELLUTILS_H_ */
