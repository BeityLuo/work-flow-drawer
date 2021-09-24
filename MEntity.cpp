#include "MEntity.h"

MEntity::MEntity(CPoint start, CPoint end, int code) : MDrawable(start, end) {
	self.setStatusCode(code);
}

void MEntity::draw(CDC* dc) {
	if (self.statusCode & self.ENTITY_STATE_SELECTED) {
		self.drawSelectPoints(dc);
	}
}

void MEntity::setStatusCode(int code) {
	self.pen.DeleteObject();
	self.statusCode = code;
	if (self.statusCode & self.ENTITY_STATE_SELECTED) {
		self.pen.CreatePen(self.DEFAULT_PEN_TYPE, self.THICK_PEN_WIDTH, self.BLACK);
	}
	else if (self.statusCode == MEntity::ENTITY_STATE_NORMAL) {
		self.pen.CreatePen(self.DEFAULT_PEN_TYPE, self.THIN_PEN_WIDTH, self.BLACK);
	}
}

void MEntity::drawSelectPoints(CDC* dc) {
	std::list<CPoint> selectPoints = self.getSelectPoints();
	for (CPoint p : selectPoints) {
		dc->Ellipse(p.x - self.SELECT_CIRCLE_RADIUS,
			p.y - self.SELECT_CIRCLE_RADIUS,
			p.x + self.SELECT_CIRCLE_RADIUS,
			p.y + self.SELECT_CIRCLE_RADIUS);
	}
}

void MRectangle::draw(CDC* dc) {
	CPen* oldPen = dc->SelectObject(&self.pen);
	dc->Rectangle(self.startPoint.x, self.startPoint.y, self.endPoint.x, self.endPoint.y);
	MEntity::draw(dc);
	dc->SelectObject(oldPen);
	
}

std::list<CPoint> MRectangle::getSelectPoints(void) {
	std::list<CPoint> pointList;
	pointList.push_back(CPoint(self.startPoint.x, self.startPoint.y));
	pointList.push_back(CPoint(self.startPoint.x, self.endPoint.y));
	pointList.push_back(CPoint(self.endPoint.x, self.startPoint.y));
	pointList.push_back(CPoint(self.endPoint.x, self.endPoint.y));

	pointList.push_back(CPoint((self.startPoint.x + self.endPoint.x) / 2, self.startPoint.y));
	pointList.push_back(CPoint((self.startPoint.x + self.endPoint.x) / 2, self.endPoint.y));
	pointList.push_back(CPoint(self.startPoint.x, (self.startPoint.y + self.endPoint.y) / 2));
	pointList.push_back(CPoint(self.endPoint.x, (self.startPoint.y + self.endPoint.y) / 2));
	return pointList;
}

bool MRectangle::isInside(CPoint point) {
	return (point.x >= self.startPoint.x && point.x <= self.endPoint.x ||
			point.x >= self.endPoint.x && point.x <= self.startPoint.x) &&
			(point.y >= self.startPoint.y && point.y <= self.endPoint.y ||
			point.y >= self.endPoint.y && point.y <= self.startPoint.y);
}

void MEllipse::draw(CDC* dc) {
	CPen* oldPen = dc->SelectObject(&self.pen);
	dc->Ellipse(self.startPoint.x, self.startPoint.y, self.endPoint.x, self.endPoint.y);
	MEntity::draw(dc);
	dc->SelectObject(oldPen);
}

std::list<CPoint> MEllipse::getSelectPoints(void) {
	std::list<CPoint> pointList;
	pointList.push_back(CPoint(self.startPoint.x, self.startPoint.y));
	pointList.push_back(CPoint(self.startPoint.x, self.endPoint.y));
	pointList.push_back(CPoint(self.endPoint.x, self.startPoint.y));
	pointList.push_back(CPoint(self.endPoint.x, self.endPoint.y));

	pointList.push_back(CPoint((self.startPoint.x + self.endPoint.x) / 2, self.startPoint.y));
	pointList.push_back(CPoint((self.startPoint.x + self.endPoint.x) / 2, self.endPoint.y));
	pointList.push_back(CPoint(self.startPoint.x, (self.startPoint.y + self.endPoint.y) / 2));
	pointList.push_back(CPoint(self.endPoint.x, (self.startPoint.y + self.endPoint.y) / 2));
	return pointList;
}

bool MEllipse::isInside(CPoint point) {
	// l: left  t: top  r: right  b: buttom
	int ltx = self.startPoint.x < self.endPoint.x ? self.startPoint.x : self.endPoint.x;
	int lty = self.startPoint.y < self.endPoint.y ? self.startPoint.y : self.endPoint.y;
	int rbx = self.startPoint.x > self.endPoint.x ? self.startPoint.x : self.endPoint.x;
	int rby = self.startPoint.y > self.endPoint.y ? self.startPoint.y : self.endPoint.y;
	int width = rbx - ltx;
	int height = rby - lty;
	if (width < height) {
		double a = height / 2.0, b = width / 2.0;
		double c = sqrt(a * a - b * b);
		double c1x = 1.0 * ltx + width / 2.0;
		double c1y = lty + a - c;
		double c2x = 1.0 * ltx + width / 2.0;
		double c2y = rby - a + c;
		double d1 = sqrt((point.x - c1x) * (point.x - c1x) + (point.y - c1y) * (point.y - c1y));
		double d2 = sqrt((point.x - c2x) * (point.x - c2x) + (point.y - c2y) * (point.y - c2y));
		if (d1 + d2 < 2 * a) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		double b = height / 2.0, a = width / 2.0;
		double c = sqrt(a * a - b * b);
		double c1x = ltx + a - c;
		double c1y = 1.0 * lty + height / 2.0;
		double c2x = rbx - a + c;
		double c2y = 1.0 * lty + height / 2.0;
		double d1 = sqrt((point.x - c1x) * (point.x - c1x) + (point.y - c1y) * (point.y - c1y));
		double d2 = sqrt((point.x - c2x) * (point.x - c2x) + (point.y - c2y) * (point.y - c2y));
		if (d1 + d2 < 2 * a) {
			return true;
		}
		else {
			return false;
		}
	}
}

void MLine::draw(CDC* dc) {
	CPen* oldPen = dc->SelectObject(&self.pen);
	dc->MoveTo(self.startPoint);
	dc->LineTo(self.endPoint);
	MEntity::draw(dc);
	dc->SelectObject(oldPen);
}

std::list<CPoint> MLine::getSelectPoints(void) {
	std::list<CPoint> pointList;
	pointList.push_back(CPoint(self.startPoint.x, self.startPoint.y));
	pointList.push_back(CPoint(self.endPoint.x, self.endPoint.y));
	pointList.push_back(CPoint((self.startPoint.x + self.endPoint.x) / 2, (self.startPoint.y + self.endPoint.y) / 2));
	return pointList;
}

bool MLine::isInside(CPoint point) {
	double x1 = self.startPoint.x, y1 = self.startPoint.y;
	double x2 = self.endPoint.x, y2 = self.endPoint.y;
	double k = (y1 - y2) / (x1 - x2), b = (x1 * y2 - x2 * y1) / (x1 - x2);
	double d = abs(k * point.x - point.y + b) / sqrt(k * k + 1);
	if (d > self.SELECT_RANGE_LEN) {
		return false;
	}
	else {
		return (point.x >= self.startPoint.x && point.x <= self.endPoint.x ||
				point.x >= self.endPoint.x && point.x <= self.startPoint.x) &&
				(point.y >= self.startPoint.y && point.y <= self.endPoint.y ||
				point.y >= self.endPoint.y && point.y <= self.startPoint.y);
	}
}


MEntity* MEntityFactory::create(MEntityType type, CPoint point, int entityStatusCode) {
	switch (type) {
	case MEntityType::RECTANGLE:
		return new MRectangle(point, point, entityStatusCode);
	case MEntityType::ELLIPSE:
		return new MEllipse(point, point, entityStatusCode);
	case MEntityType::LINE:
		return new MLine(point, point, entityStatusCode);
	}
}