#include "MOperationManager.h"

MOperationManager::MOperationManager() {
	self.positionToInsert = self.operationList.end();
}

void MOperationManager::addOperation(MOperation* operation) {
	if (self.positionToInsert != self.operationList.end()) {
		// 进到这里说明undo之后有了新的operation，要清除掉undo的operation
		for (auto ite = self.positionToInsert; ite != self.operationList.end(); ++ite) {
			delete(*ite); //销毁，必须有这一步否则内存泄漏
		}
		self.operationList.erase(self.positionToInsert, self.operationList.end());
	}
	self.operationList.push_back(operation);
	self.positionToInsert = self.operationList.end(); //这一句应该是多余的
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