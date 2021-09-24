#include"MEntity.h"
#include"MEntityManager.h"


MEntity* MEntityManager::setSelected(CPoint point) {

	MEntity* selected_entity = nullptr;
	for (MEntity* entity : self.entityList) {
		if (entity->isInside(point)) {
			selected_entity = entity;
		}
	}
	if (selected_entity != nullptr) {
		selected_entity->select();
	}
	return selected_entity;
}
MEntity* MEntityManager::setSelectedAndOthersUnselected(CPoint point) {
	MEntity* selected_entity = nullptr;
	for (MEntity* entity : self.entityList) {
		if (entity->isInside(point)) {
			selected_entity = entity;
		}
		if (entity->isSelected()) {
			entity->unselect();
		}
	}
	if (selected_entity != nullptr) {
		selected_entity->select();
		// self.entityList.remove(selected_entity); // 将选出的实体置于顶部（放到链表尾部即可）
		// self.entityList.push_back(selected_entity);
		
	}
	return selected_entity;
}
void MEntityManager::addEntity(MEntity* entity) {
	self.entityList.push_back(entity);
}
void MEntityManager::remove(MEntity* entity) {
	self.entityList.remove(entity);
}