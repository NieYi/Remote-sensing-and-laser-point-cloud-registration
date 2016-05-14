
// PCL2ImgWinView.h : CPCL2ImgWinView 类的接口
//

#pragma once
#include "SSplitter.h"
#include "ImgDlg.h"
#include "PCLDlg.h" 
#include "ProjectInfo.h"
#include "PCL2ImgWinDoc.h"

class CPCL2ImgWinView : public CView
{
protected: // 仅从序列化创建
	CPCL2ImgWinView();
	DECLARE_DYNCREATE(CPCL2ImgWinView)

// 特性
public:
	CPCL2ImgWinDoc* GetDocument() const;
private:
	CSSplitter		m_MainSplitterPane, m_RightSplitterPane;
    SIZE	m_sizeView;
	CImgDlg* m_ImgCtrl;
	CPCLDlg* m_PclCtrl;
	CProjectInfoDlg * m_ProjInfoCtrl;
	CImageList m_ImgList;
// 操作
public:
	bool m_blOnHideLeftPane; 
	bool m_blOnHideRightPane; 
	COLORREF m_RGBList[5];
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
	virtual ~CPCL2ImgWinView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHideLeftPane();
	afx_msg void OnUpdateHideLeftPane(CCmdUI *pCmdUI);
	afx_msg void OnShowLeftPane();
	afx_msg void OnUpdateShowLeftPane(CCmdUI *pCmdUI);
	afx_msg void OnHideRightPane();
	afx_msg void OnUpdateHideRightPane(CCmdUI *pCmdUI);
	afx_msg void OnShowRightPane();
	afx_msg void OnUpdateShowRightPane(CCmdUI *pCmdUI);
	afx_msg void OnSetSwitchpoint();
	afx_msg void OnUpdateSetSwitchpoint(CCmdUI *pCmdUI); 
	afx_msg void OnEditCancel();
	afx_msg void OnUpdateEditCancel(CCmdUI *pCmdUI);
	afx_msg void OnEditSure();
	afx_msg void OnUpdateEditSure(CCmdUI *pCmdUI);
	// 操作
public: 
	enum ViewStatus{
		NORMAL,
		MATCHING
	};
	ViewStatus m_Status;
	int m_EditStep;
	SwitchPoints m_SwithPoints[5];
	CListCtrl * m_CListPointsCtrl;
	int m_NowSetIndex;
	int m_HasSetCnt;
	SwitchPoints m_NowEditPoint;
	double m_CalcResult[9];
	bool m_IsCalcSuc;
	void ClearAllPoint(){ 
	    m_PclCtrl->ClearAllPoint(); 
		m_HasSetCnt = 0;
	}
	void RefreshPointsList(){
		if (!m_CListPointsCtrl)
			return;

		m_CListPointsCtrl->DeleteAllItems(); 
		TCHAR buffer[20];

		for (int i=0;i<m_HasSetCnt;i++){
			sprintf_s(buffer,20,_T("%d"),i+1);
			int nRow = m_CListPointsCtrl->InsertItem(i, buffer,i);//插入行

			//设置数据
			sprintf_s(buffer,20,_T("%.2f"),m_SwithPoints[i].point3d.x);
			m_CListPointsCtrl->SetItemText(nRow, 1, buffer);


			//设置数据
			sprintf_s(buffer,20,_T("%.2f"),m_SwithPoints[i].point3d.y);
			m_CListPointsCtrl->SetItemText(nRow, 2, buffer);


			//设置数据
			sprintf_s(buffer,20,_T("%.2f"),m_SwithPoints[i].point3d.z);
			m_CListPointsCtrl->SetItemText(nRow, 3, buffer);

			//设置数据
			sprintf_s(buffer,20,_T("%.2f"),m_SwithPoints[i].point2d.x);
			m_CListPointsCtrl->SetItemText(nRow, 4, buffer);


			//设置数据
			sprintf_s(buffer,20,_T("%.2f"),m_SwithPoints[i].point2d.y);
			m_CListPointsCtrl->SetItemText(nRow, 5, buffer);
		}
	}
	void InitPointsList(){
		if (!m_CListPointsCtrl)
			return;

		m_CListPointsCtrl->SetImageList(&m_ImgList, LVSIL_SMALL);   
		m_NowSetIndex = 0;
		m_HasSetCnt = 0;

		memset(&m_SwithPoints,NULL,sizeof(SwitchPoints));

		m_CListPointsCtrl->InsertColumn( 0, "序号", LVCFMT_LEFT, 40 );//插入列
		m_CListPointsCtrl->InsertColumn( 1, "点云X", LVCFMT_LEFT, 100 );
		m_CListPointsCtrl->InsertColumn( 2, "点云Y", LVCFMT_LEFT, 100 );
		m_CListPointsCtrl->InsertColumn( 3, "点云Z", LVCFMT_LEFT, 100 );
		m_CListPointsCtrl->InsertColumn( 4, "遥感图X", LVCFMT_LEFT, 100 );
		m_CListPointsCtrl->InsertColumn( 4, "遥感图Y", LVCFMT_LEFT, 100 ); 
	}

	void SetStatusText(LPCTSTR txt);
	void SetEditStep(int step);
	afx_msg void OnCalc();
	afx_msg void OnModify();
	afx_msg void OnUpdateModify(CCmdUI *pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnReselection();
	afx_msg void OnReSelection();
	afx_msg void OnCalAgain();
};

#ifndef _DEBUG  // PCL2ImgWinView.cpp 中的调试版本
inline CPCL2ImgWinDoc* CPCL2ImgWinView::GetDocument() const
   { return reinterpret_cast<CPCL2ImgWinDoc*>(m_pDocument); }
#endif

