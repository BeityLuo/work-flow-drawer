#ifndef M_CANVAS_MANAGER
#define M_CANVAS_MANAGER

#include <atltypes.h>
#include "tools.h"

class MCanvasManager {
private:
	CPoint* lDownPoint;
	CPoint* lUpPoint;

	MEntityManager* entityManager;

public:
	MCursorType cursorType;
	MMouseStatus mouseStatus;
	MEntity* drawingEntity;
	MRectangle* connectingEntity; 
public:
	MCanvasManager(MEntityManager* entityManager) : entityManager(entityManager) {
		self.drawingEntity = nullptr;
		self.connectingEntity = nullptr;
		self.mouseStatus = MMouseStatus::RELEASED;
		self.cursorType = MCursorType::SELECT;
	}

	void setLDownPoint(CPoint* point) {
		if (self.lDownPoint != nullptr)
			delete(self.lDownPoint);
		if (point != nullptr)
			lDownPoint = new CPoint(*point);
		else
			lDownPoint = nullptr;
	}
	CPoint* getLDownPoint() { return self.lDownPoint; }

	void setLUpPoint(CPoint* point) {
		if (self.lUpPoint != nullptr)
			delete(self.lUpPoint);
		if (point != nullptr)
			lUpPoint = new CPoint(*point);
		else
			lUpPoint = nullptr;


	}

	CPoint* getLUpPoint() { return self.lUpPoint; }
};
#endif