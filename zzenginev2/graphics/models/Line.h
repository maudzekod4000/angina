#ifndef RENDERER_PRIMITIVES_LINE_H_
#define RENDERER_PRIMITIVES_LINE_H_

#include "enginev2/graphics/models/Point.h"
#include "enginev2/graphics/models/Color.h"

class TextureRendererComponent;

class Line {
public:
	friend class TextureRendererComponent;

	Line() = default;
	Line(const Point& start, const Point& end, const Color&);
	Line(const Point& start, const Point& end, const Point& normal);

	Point getOrigin() const;
	Point getEnd() const;

	Line operator+(const Line& other) const;
	Line operator*(int32_t scalar);
	Line operator/(int32_t scalar);
	Line reversed() const;

	Line connect(const Line& other) const;
	Line midpoint(const Line& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Line&);

	Point N;
private:
	Point a;
	Point b;
	Color color;
	
};

#endif /* RENDERER_PRIMITIVES_LINE_H_ */
