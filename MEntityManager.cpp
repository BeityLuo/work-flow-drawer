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
		// self.entityList.remove(selected_entity); // ��ѡ����ʵ�����ڶ������ŵ�����β�����ɣ�
		// self.entityList.push_back(selected_entity);
		
	}
	return selected_entity;
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
		self.operationManager.addOperation(new MAddOperation(entity));
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
			self.operationManager.addOperation(new MDeleteOperation(entity));
		}
	}
	
}

void MEntityManager::remove(std::vector<MEntity*> entities) {
	for (MEntity* entity : entities) {
		self.remove(entity);
	}
}

bool MEntityManager::contains(MEntity* entity) {
	int i = 0;
	for (MEntity* e : self.entityList) {
		if (e == entity && e->getPosition() == i) return true; // ������ƣ���֤λ�õ���ȷ
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

void MEntityManager::undo() {
	// �õ����һ�β����������е�afterɾ����������е�before
	MOperation* ope = self.operationManager.getUndoOperation();
	if (ope != nullptr) {
		self.setUnrecording();
		self.remove(ope->entitiesAfter()); //���ﷵ�ص������ǿ�vector���������ǿ�ָ��
		self.addEntity(ope->entitiesBefore());
		self.setRecording();
	}
}

void MEntityManager::redo() {
	MOperation* ope = self.operationManager.getRedoOperation();
	if (ope != nullptr) {
		self.setUnrecording();
		self.remove(ope->entitiesBefore()); //��undo��˳�����෴��
		self.addEntity(ope->entitiesAfter());
		self.setRecording();
	}
}