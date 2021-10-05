#pragma once
#include<vector>
#include"MEntity.h"
#ifndef MOPERATION
#define MOPERATION
#define self (*this)



class MOperation {
protected:
	std::vector<MEntity*> before;
	std::vector<MEntity*> after;
public:
	MOperation(std::vector<MEntity*> before, std::vector<MEntity*> after);
	MOperation(MEntity* before, std::vector<MEntity*> after);
	MOperation(std::vector<MEntity*> before, MEntity* after);
	MOperation(MEntity* before, MEntity* after);
	std::vector<MEntity*> entitiesBefore() { return before; }
	std::vector<MEntity*> entitiesAfter() { return after; }
};


class MAddOperation : public MOperation {
public:
	MAddOperation(std::vector<MEntity*> entities);
	MAddOperation(MEntity* entity);
};

class MDeleteOperation : public MOperation {
public:
	MDeleteOperation(std::vector<MEntity*> entities);
	MDeleteOperation(MEntity* entity);
};

#endif