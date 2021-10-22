#pragma once
#ifndef MENTITY_MANAGER
#define MENTITY_MANAGER
#include "MEntity.h"
#include "MOperationManager.h"
#include <atltypes.h>
#include<vector>
#define self (*this)

class MEntityManager {
private:
	std::vector<MEntity*> entityList;
	MOperationManager* operationManager = new MOperationManager();
	bool isRecordingOperation;

	void setUnrecording() { self.isRecordingOperation = false; }
	void setRecording() { self.isRecordingOperation = true; }
public:
	MEntityManager() { { self.isRecordingOperation = true; } }
	void setSelected(CPoint point);
	MEntity* setSelectedAndOthersUnselected(CPoint point);
	void setSelectedArea(CRect rect);
	void reverseSelectedStatus(CPoint point);
	bool isInside(CPoint point);
	void clearSelectedStatus();

	void addEntity(MEntity* entity);
	void addEntity(std::vector<MEntity*> entities);
	void remove(MEntity* entity);
	void remove(std::vector<MEntity*> entities);
	std::vector<MEntity*> getEntityList() { return entityList; }
	std::vector<MEntity*> getSelectedEntities();
	bool contains(MEntity* entity);

	void undo();
	void redo();
	bool existsUndo() { return self.operationManager->existsUndo(); }
	bool existsRedo() { return self.operationManager->existsRedo(); }

	void moveUpSelectedEntities();
	void moveDownSelectedEntities();
	bool couldMoveUpSelectedEntities();
	bool couldMoveDownSelectedEntities();
};
#endif // !MENTITY_MANAGER