#include <afxwin.h>
#include <atltypes.h>

#ifndef MDRAWABLE
#define MDRAWABLE

#define self (*this)


class MDrawable {
protected:
	CPoint startPoint;
	CPoint endPoint;
	CPen pen;

	static const int THIN_PEN_WIDTH = 1;
	static const int THICK_PEN_WIDTH = 2;
	static const COLORREF BLACK = RGB(256, 256, 256);
	static const int DEFAULT_PEN_TYPE = PS_SOLID;
	static const int SELECT_CIRCLE_RADIUS = 5;
	
public:
	MDrawable(CPoint start, CPoint end) {
		self.startPoint.x = start.x;
		self.startPoint.y = start.y;
		self.endPoint.x = end.x;
		self.endPoint.y = end.y;
		pen.CreatePen(PS_SOLID, THIN_PEN_WIDTH, BLACK);
	}
	//void setPostion(CPoint position) { self.position = position; }
	//void setShape(int width, int height) { self.shape.width = width; self.shape.height = height; }
	void setStartAndEndPoint(CPoint start, CPoint end) {
		self.startPoint.x = start.x;
		self.startPoint.y = start.y;
		self.endPoint.x = end.x;
		self.endPoint.y = end.y;
	}
	void setEndPoint(CPoint end) {
		self.endPoint.x = end.x;
		self.endPoint.y = end.y;
	}
	// void setColor(COLORREF color) { self.pen.CreatePen(PS_SOLID, THIN_PEN_WIDTH, color); }
	virtual void draw(CDC* dc) = 0;

};
#endif // !MDRAWABLE
