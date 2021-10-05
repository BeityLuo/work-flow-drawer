#include "operations.h"

MOperation::MOperation(std::vector<MEntity*> before, std::vector<MEntity*> after) {
	for (MEntity* e : before) {
		self.before.push_back(e);
	}
	for (MEntity* e : after) {
		self.after.push_back(e);
	}
}
MOperation::MOperation(MEntity* before, MEntity* after) {
	if (before != nullptr) self.before.push_back(before);
	if (after != nullptr) self.after.push_back(after);
}

MOperation::MOperation(std::vector<MEntity*> before, MEntity* after) {
	for (MEntity* e : before) {
		self.before.push_back(e);
	}
	if (after != nullptr) self.after.push_back(after);
}
MOperation::MOperation(MEntity * before, std::vector<MEntity*> after) {
	if (before != nullptr) self.before.push_back(before);
	for (MEntity* e : after) {
		self.after.push_back(e);
	}
}


MAddOperation::MAddOperation(std::vector<MEntity*> entities) : MOperation(nullptr, entities) {}
MAddOperation::MAddOperation(MEntity* entity) : MOperation(nullptr, entity) {}

MDeleteOperation::MDeleteOperation(std::vector<MEntity*> entities) : MOperation(entities, nullptr) {}
MDeleteOperation::MDeleteOperation(MEntity* entity) : MOperation(entity, nullptr) {}