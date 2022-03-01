#pragma once
#ifndef MCONNECTABLE
#define MCONNECTABLE
#include <vector>
class MLine;
class MConnectable
{
public:
	virtual std::vector<CPoint*> getConnectPoints() = 0;
	virtual bool isOnConnectPoints(CPoint& point) = 0;
	virtual CPoint* getNearConnectPoint(CPoint& point) = 0;
	virtual void attachOutLine(MLine* line, CPoint& connectPoint) = 0;
	virtual void attachInLine(MLine* line, CPoint& connectPoint) = 0;
	virtual void setConnecting(bool b) = 0;
};

#endif
