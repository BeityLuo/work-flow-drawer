#pragma once
#include<vector>
#include"operations.h"
#ifndef MOPERATION_MANAGER
#define MOPERATION_MANAGER

class MOperationManager {
private:
	std::vector<MOperation*> operationList;
	std::vector<MOperation*>::iterator positionToInsert;
public:
	MOperationManager();
	void addOperation(MOperation* operation);
	MOperation* getUndoOperation();
	MOperation* getRedoOperation();

	bool existsUndo();
	bool existsRedo();
};

#endif // !MOPERATION_MANAGER