
// Work_Flow_DrawerView.cpp: CWorkFlowDrawerView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Work_Flow_Drawer.h"
#endif

#include "Work_Flow_DrawerDoc.h"
#include "Work_Flow_DrawerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWorkFlowDrawerView

IMPLEMENT_DYNCREATE(CWorkFlowDrawerView, CView)

BEGIN_MESSAGE_MAP(CWorkFlowDrawerView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DRAW_LINE, &CWorkFlowDrawerView::OnLine)
	ON_COMMAND(ID_DRAW_RECTANGLE, &CWorkFlowDrawerView::OnRectangle)
	ON_COMMAND(ID_DRAW_ELLIPSE, &CWorkFlowDrawerView::OnEllipse)
	ON_COMMAND(ID_DRAW_TEXT, &CWorkFlowDrawerView::OnText)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_CANCEl_DRAW, &CWorkFlowDrawerView::OnCancelDraw)
	ON_COMMAND(ID_REDO, &CWorkFlowDrawerView::OnRedo)
	ON_COMMAND(ID_UNDO, &CWorkFlowDrawerView::OnUndo)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, &CWorkFlowDrawerView::OnUpdateDrawLine)
	ON_COMMAND(ID_EDIT_DELETE, &CWorkFlowDrawerView::OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_REDO, &CWorkFlowDrawerView::OnUpdateRedo)
	ON_UPDATE_COMMAND_UI(ID_UNDO, &CWorkFlowDrawerView::OnUpdateUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, &CWorkFlowDrawerView::OnUpdateEditDelete)
	ON_COMMAND(ID_32785, &CWorkFlowDrawerView::OnMoveUp)
	ON_COMMAND(ID_32786, &CWorkFlowDrawerView::OnMoveDown)
	ON_UPDATE_COMMAND_UI(ID_32785, &CWorkFlowDrawerView::OnUpdateMoveUp)
	ON_UPDATE_COMMAND_UI(ID_32786, &CWorkFlowDrawerView::OnUpdateMoveDown)
END_MESSAGE_MAP()

// CWorkFlowDrawerView 构造/析构

CWorkFlowDrawerView::CWorkFlowDrawerView() noexcept
{
	// TODO: 在此处添加构造代码
	/*CWorkFlowDrawerDoc* pDoc = self.GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;*/
	// 暂时不用Doc类了
	self.entityManager = new MEntityManager();
	self.drawingEntity = nullptr;
	self.mouseStatus = MMouseStatus::RELEASED;
	self.mouseType = MMouseType::SELECT;
}

CWorkFlowDrawerView::~CWorkFlowDrawerView()
{
}

BOOL CWorkFlowDrawerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}




// CWorkFlowDrawerView 打印

BOOL CWorkFlowDrawerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CWorkFlowDrawerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CWorkFlowDrawerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CWorkFlowDrawerView 诊断

#ifdef _DEBUG
void CWorkFlowDrawerView::AssertValid() const
{
	CView::AssertValid();
}

void CWorkFlowDrawerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWorkFlowDrawerDoc* CWorkFlowDrawerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorkFlowDrawerDoc)));
	return (CWorkFlowDrawerDoc*)m_pDocument;
}
#endif //_DEBUG

// CWorkFlowDrawerView 绘图

void CWorkFlowDrawerView::OnDraw(CDC* pDC)
{


	// TODO: 在此处为本机数据添加绘制代码
	for (MEntity* entity : self.entityManager->getEntityList()) {
		entity->draw(pDC);
	}
}


// CWorkFlowDrawerView 消息处理程序

// 绘制直线
void CWorkFlowDrawerView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	self.mouseType = MMouseType::DRAW_LINE;
	// 不加的话，在“按下”按钮之后，处于PRESSED且非SELECET状态，再触发mouseMove就会绘图.
	// 然而这时候还没有创建对象，所以会出错
	self.mouseStatus = MMouseStatus::RELEASED; 
}


// 绘制矩形
void CWorkFlowDrawerView::OnRectangle()
{
	// TODO: 在此添加命令处理程序代码
	self.mouseType = MMouseType::DRAW_RECTANGLE;
	self.mouseStatus = MMouseStatus::RELEASED;
}


// 绘制椭圆
void CWorkFlowDrawerView::OnEllipse()
{
	// TODO: 在此添加命令处理程序代码
	self.mouseType = MMouseType::DRAW_ELLIPSE;
	self.mouseStatus = MMouseStatus::RELEASED;
}


// 绘制文本
void CWorkFlowDrawerView::OnText()
{
	// TODO: 在此添加命令处理程序代码
	self.mouseType = MMouseType::DRAW_TEXT;
	self.mouseStatus = MMouseStatus::RELEASED;
}
void CWorkFlowDrawerView::OnCancelDraw()
{
	// TODO: 在此添加命令处理程序代码
	self.mouseType = MMouseType::SELECT;
}

void CWorkFlowDrawerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	self.startPoint = self.endPoint = point;
	self.mouseStatus = MMouseStatus::PRESSED;
	
	if (self.drawingEntity != nullptr) {
		// 如果有正在选中的东西，取消他的选中状态
		self.drawingEntity->unselect();
	}
	if (self.mouseType != MMouseType::SELECT) {
		// 绘图状态
		MEntity* entity = MEntityFactory::create(mouseType2EntityType(self.mouseType), point, MEntity::ENTITY_STATE_SELECTED);
		self.drawingEntity = entity;
		self.entityManager->addEntity(entity);
	}

	
	CView::OnLButtonDown(nFlags, point);
}


void CWorkFlowDrawerView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	
	if (self.mouseStatus == MMouseStatus::PRESSED &&
		self.mouseType != MMouseType::SELECT) {
		// 左键按下且处于"非选择（绘图）"状态
		self.drawingEntity->setEndPoint(point);
		             
		self.repaint();
	}
	else if (self.mouseStatus == MMouseStatus::PRESSED &&
		self.mouseType == MMouseType::SELECT) {
		
		// 
		self.entityManager->setSelectedArea(CRect(self.startPoint, self.endPoint));
		CDC* pDC = GetDC();
		pDC->SetROP2(R2_XORPEN);
		CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
		CPen* pen = new CPen(PS_SOLID, 1, RGB(0, 255, 0));
		CPen* oldPen = pDC->SelectObject(pen);
		pDC->Rectangle(self.startPoint.x, self.startPoint.y, self.endPoint.x, self.endPoint.y);
		pDC->Rectangle(self.startPoint.x, self.startPoint.y, point.x, point.y);
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(oldPen);
		ReleaseDC(pDC);
	}
	self.endPoint = point;
	CView::OnMouseMove(nFlags, point);
}


void CWorkFlowDrawerView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	mouseStatus = MMouseStatus::RELEASED;
	
	self.endPoint = point;

	
	if (self.mouseType == MMouseType::SELECT) {
		// 处于选择状态下抬起鼠标时，将开始点设置为“选中”
		if (self.entityManager->isInside(self.startPoint)) {
			self.entityManager->reverseSelectedStatus(self.startPoint);
		}
		else {
			self.entityManager->clearSelectedStatus();
		}
		
	} else{
		// 绘画状态
		if (self.startPoint.x == point.x && self.startPoint.y == point.y) {
			// 如果开始和结束的点相同，就删除该entity
			self.entityManager->remove(self.drawingEntity);
		}
		self.drawingEntity = nullptr;
		self.mouseType = MMouseType::SELECT; // 恢复鼠标状态为“选择”
	}
	self.repaint();
	CView::OnLButtonUp(nFlags, point);

}


void CWorkFlowDrawerView::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 在此处添加消息处理程序代码
}

void CWorkFlowDrawerView::OnUndo()
{
	// TODO: 在此添加命令处理程序代码
	self.entityManager->undo();
	self.repaint();
}

void CWorkFlowDrawerView::OnRedo()
{
	// TODO: 在此添加命令处理程序代码
	self.entityManager->redo();
	self.repaint();
}
//int i = 0;
void CWorkFlowDrawerView::OnUpdateDrawLine(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	// 当前鼠标正在画线的时候，将画线按钮设置为disable
	if (self.mouseType == MMouseType::DRAW_LINE) {
		pCmdUI->Enable(false);
	}
	else {
		pCmdUI->Enable(true);
	}
}

void CWorkFlowDrawerView::OnEditDelete()
{
	// TODO: 在此添加命令处理程序代码
	std::vector<MEntity*> entities = self.entityManager->getSelectedEntities();
	self.entityManager->remove(entities);
	CRect rect;
	GetClientRect(rect);
	self.InvalidateRect(rect);
}

void CWorkFlowDrawerView::OnUpdateRedo(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (self.entityManager->existsRedo()) {
		pCmdUI->Enable(true);
	}
	else {
		pCmdUI->Enable(false);
	}
}

void CWorkFlowDrawerView::OnUpdateUndo(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (self.entityManager->existsUndo()) {
		pCmdUI->Enable(true);
	}
	else {
		pCmdUI->Enable(false);
	}
}

void CWorkFlowDrawerView::OnUpdateEditDelete(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (self.entityManager->getSelectedEntities().size() != 0) {
		pCmdUI->Enable(true);
	}
	else {
		pCmdUI->Enable(false);
	}
}

void CWorkFlowDrawerView::OnMoveUp()
{
	self.entityManager->moveUpSelectedEntities();
	self.repaint();
}


void CWorkFlowDrawerView::OnMoveDown()
{
	self.entityManager->moveDownSelectedEntities();
	self.repaint();
}


void CWorkFlowDrawerView::OnUpdateMoveUp(CCmdUI* pCmdUI)
{
	if (self.entityManager->couldMoveUpSelectedEntities())
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}


void CWorkFlowDrawerView::OnUpdateMoveDown(CCmdUI* pCmdUI)
{
	if (self.entityManager->couldMoveDownSelectedEntities())
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}
