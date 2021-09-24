#pragma once
#ifndef MENTITY_MANAGER
#define MENTITY_MANAGER
#include "MEntity.h"
#include <atltypes.h>
#include<list>

class MEntityManager {
private:
	std::list<MEntity*> entityList;
public:
	MEntity* setSelected(CPoint point);
	MEntity* setSelectedAndOthersUnselected(CPoint point);
	void addEntity(MEntity* entity);
	void remove(MEntity* entity);
	std::list<MEntity*> getEntityList() { return entityList; }
};
#endif // !MENTITY_MANAGER