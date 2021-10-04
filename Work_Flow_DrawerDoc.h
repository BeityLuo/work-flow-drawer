#include "MEntityManager.h"
#include "MOperationManager.h"
// Work_Flow_DrawerDoc.h: CWorkFlowDrawerDoc 类的接口
//


#pragma once


class CWorkFlowDrawerDoc : public CDocument
{
private:
	MEntityManager* entityManager;
	MOperationManager* operationManager;
protected: // 仅从序列化创建
	CWorkFlowDrawerDoc() noexcept;
	DECLARE_DYNCREATE(CWorkFlowDrawerDoc)

// 特性
public:

// 操作
public:
	MEntityManager* getEntityManager() { return self.entityManager; }
	MOperationManager* getOperationManager() { return self.operationManager; }

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CWorkFlowDrawerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
