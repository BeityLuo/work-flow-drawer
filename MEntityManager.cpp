#include"MEntity.h"
#include"MEntityManager.h"
#include<algorithm>


void MEntityManager::setSelected(CPoint point) {

	MEntity* selected_entity = nullptr;
	for (MEntity* entity : self.entityList) {
		if (entity->isInside(point)) {
			selected_entity = entity;
		}
	}
	if (selected_entity != nullptr) {
		selected_entity->select();
	}
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
	}
	return selected_entity;
}
void MEntityManager::setSelectedArea(CRect rect) {
	
}

void MEntityManager::reverseSelectedStatus(CPoint point) {
	MEntity* selected_entity = nullptr;
	for (MEntity* entity : self.entityList) {
		if (entity->isInside(point)) {
			selected_entity = entity; // the top entity
		}
	}
	if (selected_entity != nullptr) {
		selected_entity->isSelected() ? selected_entity->unselect() : selected_entity->select();
	}
}

bool MEntityManager::isInside(CPoint point) {
	for (MEntity* entity : self.entityList) {
		if (entity->isInside(point)) {
			return true;
		}
	}
	return false;
}

void MEntityManager::clearSelectedStatus() {
	for (MEntity* entity : self.entityList) {
		entity->unselect();
	}
}

void MEntityManager::addEntity(MEntity* entity) {
	if (entity->hasPosition()) {
		std::vector<MEntity*>::iterator ite = self.entityList.begin() + entity->getPosition();
		self.entityList.insert(ite, entity);
		ite = self.entityList.begin() + entity->getPosition();
		//������һ����iteָ��entity������Ҫ���º���entity
		for (++ite; ite != self.entityList.end(); ++ite) {
			(*ite)->setPosition((*ite)->getPosition() + 1);
		}
	}
	else {
		//����û�б����ù�λ�ã���Ҫ����positionΪ���һ��
		entity->setPosition(self.entityList.size()); 
		self.entityList.push_back(entity);
		
	}
	if (self.isRecordingOperation) {
		self.operationManager->addOperation(new MAddOperation(entity));
	}
}
void MEntityManager::addEntity(std::vector<MEntity*> entities) {
	for (MEntity* e : entities) {
		self.addEntity(e);
	}
}

void MEntityManager::remove(MEntity* entity) {
	if (self.contains(entity)) {
		self.entityList.erase(self.entityList.begin() + entity->getPosition());
		for (auto it = self.entityList.begin() + entity->getPosition(); it != self.entityList.end(); ++it) {
			(*it)->setPosition((*it)->getPosition() - 1);
		}
		if (self.isRecordingOperation) {
			self.operationManager->addOperation(new MDeleteOperation(entity));
		}
	}
	
}

void MEntityManager::remove(std::vector<MEntity*> entities) {
	if (self.isRecordingOperation) {
		// ��Ҫ����Ӳ�������Ϊ
		self.operationManager->addOperation(new MDeleteOperation(entities));
		self.setUnrecording();
		int i = 0;
		for (MEntity* entity : entities) {
			if (self.contains(entity)) {
				self.entityList.erase(self.entityList.begin() + (entity->getPosition() - i++));
			}
		}
		i = 0;
		for (MEntity* entity : self.entityList) {
			entity->setPosition(i++);
		}
		self.setRecording();
	}
	else {
		for (MEntity* entity : entities) {
			self.remove(entity);
		}
	}
}

bool MEntityManager::contains(MEntity* entity) {
	int i = 0;
	for (MEntity* e : self.entityList) {
		if (e->equals(entity)) return true; // ������ƣ���֤λ�õ���ȷ
		i++;
	}
	return false;
}

std::vector<MEntity*> MEntityManager::getSelectedEntities() {
	std::vector<MEntity*> ans;
	for (MEntity* entity : self.entityList) {
		if (entity->isSelected()) {
			ans.push_back(entity);
		}
	}
	return ans;
}
bool greaterSort(MEntity* a, MEntity* b) {
	return a->getPosition() > b->getPosition();
}
bool lessSort(MEntity* a, MEntity* b) {
	return a->getPosition() < b->getPosition();
}
void MEntityManager::undo() {
	// �õ����һ�β����������е�afterɾ����������е�before
	MOperation* ope = self.operationManager->getUndoOperation();
	if (ope != nullptr) {
		self.setUnrecording();
		std::vector<MEntity*>& after = ope->entitiesAfter();
		// ����
		std::sort(after.begin(), after.end(), greaterSort);
		self.remove(after); //���ﷵ�ص������ǿ�vector���������ǿ�ָ��

		std::vector<MEntity*> &before = ope->entitiesBefore();
		std::sort(before.begin(), before.end(), lessSort);
		self.addEntity(before);
		self.setRecording();
	}
}

void MEntityManager::redo() {
	MOperation* ope = self.operationManager->getRedoOperation();
	if (ope != nullptr) {
		self.setUnrecording();
		std::vector<MEntity*>& before = ope->entitiesBefore();
		// ����
		std::sort(before.begin(), before.end(), greaterSort);
		self.remove(before); //���ﷵ�ص������ǿ�vector���������ǿ�ָ��

		std::vector<MEntity*>& after = ope->entitiesAfter();
		std::sort(after.begin(), after.end(), lessSort);
		self.addEntity(after);
		self.setRecording();
	}
}

void MEntityManager::moveUpSelectedEntities() {
	if (!self.entityList.empty()) {
		MEntity* temp;
		std::vector<MEntity*> before;
		std::vector<MEntity*> after;
		for (auto it = self.entityList.rbegin() + 1; it != self.entityList.rend(); ++it) {
			if ((*it)->isSelected() && !(*(it - 1))->isSelected()) {
				before.push_back(*it);
				*it = (*it)->copy();
				(*it)->setPosition((*it)->getPosition() + 1);
				after.push_back(*it);
				(*(it - 1))->setPosition((*(it - 1))->getPosition() - 1);
				temp = *it;
				*it = *(it - 1);
				*(it - 1) = temp;
				
			}
		}
		if (!before.empty()) {
			self.operationManager->addOperation(new MChangeLayerOperation(before, after));
		}
	}
}
void MEntityManager::moveDownSelectedEntities() {
	if (!self.entityList.empty()) {
		MEntity* temp;
		std::vector<MEntity*> before;
		std::vector<MEntity*> after;
		for (auto it = self.entityList.begin() + 1; it != self.entityList.end(); ++it) {
			if ((*it)->isSelected() && !(*(it - 1))->isSelected()) {
				before.push_back(*it);
				*it = (*it)->copy();
				(*it)->setPosition((*it)->getPosition() - 1);
				after.push_back(*it);
				(*(it - 1))->setPosition((*(it - 1))->getPosition() + 1);
				temp = *it;
				*it = *(it - 1);
				*(it - 1) = temp;
			}
		}
		if (!before.empty()) {
			self.operationManager->addOperation(new MChangeLayerOperation(before, after));
		}
	}
}
bool MEntityManager::couldMoveUpSelectedEntities() {
	// Ч�ʼ������
	if (!self.entityList.empty()) {
		for (auto it = self.entityList.rbegin() + 1; it != self.entityList.rend(); ++it) {
			if ((*it)->isSelected() && !(*(it - 1))->isSelected()) {
				return true;
			}
		}
	}
	return false;
}
bool MEntityManager::couldMoveDownSelectedEntities() {
	if (!self.entityList.empty()) {
		for (auto it = self.entityList.begin() + 1; it != self.entityList.end(); ++it) {
			if ((*it)->isSelected() && !(*(it - 1))->isSelected()) {
				return true;
			}
		}
	}
	return false;
}