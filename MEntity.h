#pragma once
#include "MDrawable.h"
#include <atltypes.h>

#include<list>
#ifndef MENTITY
#define MENTITY




#define self (*this)

enum class MEntityType {
	RECTANGLE, ELLIPSE, LINE, TEXT
};





class MEntity : public MDrawable{
	public:
		static const int ENTITY_STATE_SELECTED = 0x00000001;
		static const int ENTITY_STATE_FOCUSED = 0x00000010;
		static const int ENTITY_STATE_NORMAL = 0x00000000;
		

		
	protected:
		int statusCode = ENTITY_STATE_NORMAL;
		int position;
	private:
		void setStatusCode(int code);
	public:
		MEntity(CPoint start, CPoint end, int statusCode = ENTITY_STATE_SELECTED, int position = -1);
		bool isSelected() { return self.statusCode & self.ENTITY_STATE_SELECTED; }
		void select() { setStatusCode(self.ENTITY_STATE_SELECTED); }
		void unselect() { setStatusCode(self.ENTITY_STATE_NORMAL); }
		virtual void draw(CDC* dc);
		virtual std::list<CPoint> getSelectPoints() = 0;
		void drawSelectPoints(CDC* dc);
		virtual bool isInside(CPoint point) = 0;

		int getPosition() { return self.position; }
		void setPosition(int p) { self.position = p; }
		bool hasPosition() { return self.position != -1; }

		virtual MEntity* copy() = 0;
		bool equals(MEntity* entity);
	
};

class MRectangle : public MEntity {
public:
	MRectangle(CPoint start, CPoint end, int statusCode = ENTITY_STATE_SELECTED, int position = -1) :
		MEntity(start, end, statusCode, position) {}
	void draw(CDC* dc);
	std::list<CPoint> getSelectPoints(void);
	bool isInside(CPoint point);
	MEntity* copy() { return new MRectangle(self.startPoint, self.endPoint, self.statusCode, self.position); }
};

class MEllipse : public MEntity {
public:
	MEllipse(CPoint start, CPoint end, int statusCode = ENTITY_STATE_SELECTED, int position = -1) :
		MEntity(start, end, statusCode, position) {}
	void draw(CDC* dc);
	std::list<CPoint> getSelectPoints(void);
	bool isInside(CPoint point);
	MEntity* copy() { return new MEllipse(self.startPoint, self.endPoint, self.statusCode, self.position); }
};

class MLine : public MEntity {
public:
	static const int SELECT_RANGE_LEN = 4;
public:
	MLine(CPoint start, CPoint end, int statusCode = ENTITY_STATE_SELECTED, int position = -1) :
		MEntity(start, end, statusCode, position) {}
	void draw(CDC* dc);
	std::list<CPoint> getSelectPoints(void);
	bool isInside(CPoint point);
	MEntity* copy() { return new MLine(self.startPoint, self.endPoint, self.statusCode, self.position); }
};



class MEntityFactory {
public:
	static MEntity* create(MEntityType type, CPoint point, int entityStatusCode);
};
#endif // !MENTITY