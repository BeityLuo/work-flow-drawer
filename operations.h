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
	MOperation(std::vector<MEntity*> before);
	MOperation(MEntity* entity);
	std::vector<MEntity*> entitiesBefore() { return before; }
	std::vector<MEntity*> entitiesAfter() { return after; }
};


class MAddOperation : public MOperation {
	MAddOperation(std::vector<MEntity*> before);
	MAddOperation(MEntity* entity);
};

class MDeleteOperation : public MOperation {
	MDeleteOperation(std::vector<MEntity*> before);
	MDeleteOperation(MEntity* entity);
};

#endif