#include "operations.h"

MOperation::MOperation(std::vector<MEntity*> before) {
	for (MEntity* e : before) {
		self.before.push_back(e);
	}
}
MOperation::MOperation(MEntity* entity) {
	self.before.push_back(entity);
}

MAddOperation::MAddOperation(std::vector<MEntity*> before) : MOperation(before) {}
MAddOperation::MAddOperation(MEntity* entity) : MOperation(entity){}

MDeleteOperation::MDeleteOperation(std::vector<MEntity*> before) : MOperation(before) {}
MDeleteOperation::MDeleteOperation(MEntity* entity) : MOperation(entity) {}