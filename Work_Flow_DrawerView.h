
// Work_Flow_DrawerView.h: CWorkFlowDrawerView 类的接口
//

#pragma once
#include "tools.h"
#include"MOperationManager.h"


class CWorkFlowDrawerView : public CView
{

private:
	MMouseType mouseType;
	MMouseStatus mouseStatus;
	CPoint startPoint, endPoint;

	MEntityManager* entityManager;
	// MEntityDrawer* entityDrawer;
	MEntity* selectedEntity;
	MOperationManager* operationManager;
	
protected: // 仅从序列化创建
	CWorkFlowDrawerView() noexcept;
	DECLARE_DYNCREATE(CWorkFlowDrawerView)

// 特性
public:
	CWorkFlowDrawerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CWorkFlowDrawerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLine();
	afx_msg void OnRectangle();
	afx_msg void OnEllipse();
	afx_msg void OnText();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCancelDraw();
	afx_msg void OnRedo();
	afx_msg void OnUndo();
	afx_msg void OnUpdateDrawLine(CCmdUI* pCmdUI);
	afx_msg void OnEditDelete();
};

#ifndef _DEBUG  // Work_Flow_DrawerView.cpp 中的调试版本
inline CWorkFlowDrawerDoc* CWorkFlowDrawerView::GetDocument() const
   { return reinterpret_cast<CWorkFlowDrawerDoc*>(m_pDocument); }
#endif

