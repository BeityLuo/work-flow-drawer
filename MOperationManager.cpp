#include "MOperationManager.h"

MOperationManager::MOperationManager() {
	self.positionToInsert = self.operationList.end();
}

void MOperationManager::addOperation(MOperation* operation) {
	if (self.positionToInsert != self.operationList.end()) {
		// ��������˵��undo֮�������µ�operation��Ҫ�����undo��operation
		for (auto ite = self.positionToInsert; ite != self.operationList.end(); ++ite) {
			delete(*ite); //���٣���������һ�������ڴ�й©
		}
		self.operationList.erase(self.positionToInsert, self.operationList.end());
	}
	self.operationList.push_back(operation);
	self.positionToInsert = self.operationList.end(); //��һ��Ӧ���Ƕ����
}

MOperation* MOperationManager::getUndoOperation() {
	if (self.operationList.empty()) {
		return nullptr;
	}
	else {
		--self.positionToInsert;
		return *self.positionToInsert;
	}
}

MOperation* MOperationManager::getRedoOperation() {
	if (self.positionToInsert == self.operationList.end()) {
		return nullptr;
	}
	else {
		++self.positionToInsert;
		return *(self.positionToInsert - 1);
	}
}