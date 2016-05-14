
// PCL2ImgWinView.cpp : CPCL2ImgWinView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "PCL2ImgWin.h"
#endif
#include<cstring>
#include "PCL2ImgWinDoc.h"
#include "PCL2ImgWinView.h"
#include "MainFrm.h"
#include "GXFC.h"

#include "Init.h"//包含初始化对话框的头文件
#include "TiShi.h"
#include <iomanip>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPCL2ImgWinView

IMPLEMENT_DYNCREATE(CPCL2ImgWinView, CView)

BEGIN_MESSAGE_MAP(CPCL2ImgWinView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint) 
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_COMMAND(ID_HIDE_LEFT_PANE, &CPCL2ImgWinView::OnHideLeftPane)
	ON_UPDATE_COMMAND_UI(ID_HIDE_LEFT_PANE, &CPCL2ImgWinView::OnUpdateHideLeftPane)
	ON_COMMAND(ID_SHOW_LEFT_PANE, &CPCL2ImgWinView::OnShowLeftPane)
	ON_UPDATE_COMMAND_UI(ID_SHOW_LEFT_PANE, &CPCL2ImgWinView::OnUpdateShowLeftPane)
	ON_COMMAND(ID_HIDE_RIGHT_PANE, &CPCL2ImgWinView::OnHideRightPane)
	ON_UPDATE_COMMAND_UI(ID_HIDE_RIGHT_PANE, &CPCL2ImgWinView::OnUpdateHideRightPane)
	ON_COMMAND(ID_SHOW_RIGHT_PANE, &CPCL2ImgWinView::OnShowRightPane)
	ON_UPDATE_COMMAND_UI(ID_SHOW_RIGHT_PANE, &CPCL2ImgWinView::OnUpdateShowRightPane)
	ON_COMMAND(ID_SET_SWITCHPOINT, &CPCL2ImgWinView::OnSetSwitchpoint)
	ON_UPDATE_COMMAND_UI(ID_SET_SWITCHPOINT, &CPCL2ImgWinView::OnUpdateSetSwitchpoint)
	ON_COMMAND(ID_EDIT_CANCEL, &CPCL2ImgWinView::OnEditCancel)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CANCEL, &CPCL2ImgWinView::OnUpdateEditCancel)
	ON_COMMAND(ID_EDIT_SURE, &CPCL2ImgWinView::OnEditSure)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SURE, &CPCL2ImgWinView::OnUpdateEditSure)
	ON_COMMAND(ID_CALC, &CPCL2ImgWinView::OnCalc)
	ON_COMMAND(ID_MODIFY, &CPCL2ImgWinView::OnModify)
	ON_UPDATE_COMMAND_UI(ID_MODIFY, &CPCL2ImgWinView::OnUpdateModify)
	ON_WM_CLOSE()
	
	
END_MESSAGE_MAP()

// CPCL2ImgWinView 构造/析构

CPCL2ImgWinView::CPCL2ImgWinView() 
{
	// TODO: 在此处添加构造代码
	m_blOnHideLeftPane= false; 
	m_blOnHideRightPane= false;
	m_IsCalcSuc = false;

	m_RGBList[0] = RGB(255,0,0);
	m_RGBList[1] = RGB(0,255,0);
	m_RGBList[2] = RGB(0,0,255);
	m_RGBList[3] = RGB(255,0,255);
	m_RGBList[4] = RGB(0,255,255);

	m_ImgList.Create (16,16,ILC_COLOR24 ,5,1);
	CBitmap bitmap;

	bitmap.LoadBitmap(IDB_BITMAP1);
	m_ImgList.Add (&bitmap,RGB(0,0,0));
	bitmap.Detach (); //在加载前先释放位图

	bitmap.LoadBitmap(IDB_BITMAP2);
	m_ImgList.Add (&bitmap,RGB(0,0,0));
	bitmap.Detach (); //在加载前先释放位图

	bitmap.LoadBitmap(IDB_BITMAP3);
	m_ImgList.Add (&bitmap,RGB(0,0,0));
	bitmap.Detach (); //在加载前先释放位图

	bitmap.LoadBitmap(IDB_BITMAP4);
	m_ImgList.Add (&bitmap,RGB(0,0,0));
	bitmap.Detach (); //在加载前先释放位图

	bitmap.LoadBitmap(IDB_BITMAP5);
	m_ImgList.Add (&bitmap,RGB(0,0,0));
	bitmap.Detach (); //在加载前先释放位图

}

CPCL2ImgWinView::~CPCL2ImgWinView()
{
	if (m_PclCtrl  != NULL)
		delete m_PclCtrl; 
    if (m_ImgCtrl  != NULL)
		delete m_ImgCtrl;  
	if (m_ProjInfoCtrl  != NULL)
		delete m_ProjInfoCtrl;
}

BOOL CPCL2ImgWinView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPCL2ImgWinView 绘制

void CPCL2ImgWinView::OnDraw(CDC* /*pDC*/)
{
	CPCL2ImgWinDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}
 

BOOL CPCL2ImgWinView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPCL2ImgWinView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPCL2ImgWinView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CPCL2ImgWinView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPCL2ImgWinView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{ 
}


// CPCL2ImgWinView 诊断

#ifdef _DEBUG
void CPCL2ImgWinView::AssertValid() const
{
	CView::AssertValid();
}

void CPCL2ImgWinView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPCL2ImgWinDoc* CPCL2ImgWinView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCL2ImgWinDoc)));
	return (CPCL2ImgWinDoc*)m_pDocument;
}
#endif //_DEBUG


// CPCL2ImgWinView 消息处理程序
void CPCL2ImgWinView::OnInitialUpdate()
{
	
	GetParentFrame()->RecalcLayout();

	//自动缩放到当前窗口的大小视区大小
    //SetScaleToFitSize(m_sizeView);

	//取得默认区域的
	CRect rect;
	GetClientRect( &rect );
	rect.DeflateRect(20,20); 
 
	m_PclCtrl = new CPCLDlg();
	m_PclCtrl->CreateEx(NULL,NULL, "PCL",WS_CHILD|WS_VISIBLE, rect, this, IDC_PCL, NULL);  
	m_PclCtrl->ShowWindow(SW_SHOW);/*
	m_PclCtrl->ReadLasFile("F:\\Projects\\温\\2015715宰大卫\\project2015713\\project2015713\\sh.las");*/

	m_ProjInfoCtrl = new CProjectInfoDlg();
	m_ProjInfoCtrl->CreateEx(NULL,NULL, "PROJINFO",WS_CHILD|WS_VISIBLE, rect, this, IDC_NAVIGATION, NULL); 

    m_ImgCtrl = new CImgDlg();
	m_ImgCtrl->CreateEx(NULL,NULL, "IMG",WS_CHILD|WS_VISIBLE, rect, this, IDC_IMG, NULL);
    m_ImgCtrl->OnInit();
    //绑定
	m_ImgCtrl->SetNavigation(m_ProjInfoCtrl->GetNavigationWnd());
    m_ProjInfoCtrl->GetNavigationWnd()->SetImgDlg(m_ImgCtrl);
	m_ImgCtrl->ShowWindow(SW_SHOW);
 
	m_RightSplitterPane.Create( 
		WS_CHILD|WS_VISIBLE|/*WS_BORDER|*/WS_CLIPCHILDREN|SS_HORIZ, 		 
		this,				// the parent of the splitter pane
		m_ImgCtrl,		// top pane
		m_ProjInfoCtrl,		// bottom pane
		IDC_HORIZ_SPLITTER,	// this ID is used for saving/restoring splitter
							// position and therefore it must be unique 
							// within your application
		rect,				// dimensions of the splitter pane
		90,	// m_nMaxTop value, i.e. top constraint for splitter position  
		110	// m_nMaxBottom value, i.e. bottom constraint for splitter position
	);

	m_MainSplitterPane.Create(
		WS_CHILD|WS_VISIBLE|WS_BORDER|WS_CLIPCHILDREN|SS_VERT, 		 
		this,				// the parent of the splitter pane
		m_PclCtrl,		// left pane
		&m_RightSplitterPane,// right nested pane
		IDC_VERT_SPLITTER,	// this ID is used for saving/restoring splitter
							// position and therefore it must be unique 
							// within your application
		rect,				// dimensions of the splitter pane
		90,	// m_nMaxLeft value, i.e. left constraint for splitter position
		110 // m_nMaxRight value, i.e. right constraint for splitter position
	); 

	m_CListPointsCtrl = m_ProjInfoCtrl->GetPointsListWnd();
    InitPointsList();

	m_ProjInfoCtrl->LoadImage(_argc[1]);
	m_ImgCtrl->LoadImage(_argc[1]);
	m_PclCtrl->ReadLasFile(_argc[0]);
	CView::OnInitialUpdate();
}
 
void CPCL2ImgWinView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if ( m_MainSplitterPane.GetSafeHwnd() ){
		CRect rect;
		GetClientRect( &rect );
		rect.DeflateRect(20,20);
		m_MainSplitterPane.MoveWindow(&rect); 
	}
}


void CPCL2ImgWinView::OnHideLeftPane()
{ 
	m_MainSplitterPane.HideLeftPane(); 
	m_blOnHideLeftPane = !m_blOnHideLeftPane;
}


void CPCL2ImgWinView::OnUpdateHideLeftPane(CCmdUI *pCmdUI)
{ 
	pCmdUI->Enable((!m_blOnHideRightPane));
	pCmdUI->SetCheck(m_blOnHideLeftPane);
}


void CPCL2ImgWinView::OnShowLeftPane()
{ 
	m_MainSplitterPane.ShowLeftPane();
	m_blOnHideLeftPane = !m_blOnHideLeftPane;
}


void CPCL2ImgWinView::OnUpdateShowLeftPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((!m_blOnHideRightPane));
	pCmdUI->SetCheck(!m_blOnHideLeftPane);
}


void CPCL2ImgWinView::OnHideRightPane()
{
	m_MainSplitterPane.HideRightPane();
    m_blOnHideRightPane = !m_blOnHideRightPane;
}


void CPCL2ImgWinView::OnUpdateHideRightPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((!m_blOnHideLeftPane));
	pCmdUI->SetCheck(m_blOnHideRightPane);
}


void CPCL2ImgWinView::OnShowRightPane()
{
	 m_MainSplitterPane.ShowRightPane();	
	 m_blOnHideRightPane= !m_blOnHideRightPane;
}


void CPCL2ImgWinView::OnUpdateShowRightPane(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((!m_blOnHideLeftPane));
	pCmdUI->SetCheck(!m_blOnHideRightPane);
}


void CPCL2ImgWinView::OnSetSwitchpoint()
{
	if (m_HasSetCnt >= 5)
	{
		AfxMessageBox(_T("最多只需要5对点！"));
		return;
	}

	m_NowSetIndex = m_HasSetCnt; 
	memset(&m_NowEditPoint,NULL,sizeof(SwitchPoints));

	// TODO: 在此添加命令处理程序代码
	m_Status = MATCHING;
	SetEditStep(0);

	SetStatusText(_T("请在按Shift + 鼠标左键在视图中选择点！"));
}


void CPCL2ImgWinView::OnUpdateSetSwitchpoint(CCmdUI *pCmdUI)
{ 
	bool isEditing = (m_Status == MATCHING);

	pCmdUI->Enable(!isEditing); 
}

void CPCL2ImgWinView::SetEditStep(int step){
	if (m_EditStep < step)
		m_EditStep = step; 
    SetStatusText(_T("请在按Shift + 鼠标左键在视图中选择点！"));
}
 

void CPCL2ImgWinView::OnEditCancel()
{
	if (m_EditStep == 1){ 
		m_PclCtrl->RemovePointCloud(m_NowSetIndex);
	}

	m_Status = NORMAL;
	SetEditStep(-1);
	 
}


void CPCL2ImgWinView::OnUpdateEditCancel(CCmdUI *pCmdUI)
{
	bool isEditing = (m_Status == MATCHING); 
	pCmdUI->Enable(isEditing);
}


void CPCL2ImgWinView::OnEditSure()
{
	if (m_EditStep == 0){
		 SetStatusText(_T("请在在点云中选择点"));
		 return;
	}

	if (m_EditStep == 1){
		SetStatusText(_T("请在遥感图像中选择点"));
		return;
	} 

	m_Status = NORMAL;
	SetEditStep(-1);

	m_SwithPoints[m_NowSetIndex] = m_NowEditPoint;
	if (m_HasSetCnt ==  m_NowSetIndex)
		m_HasSetCnt++;
	RefreshPointsList();
}


void CPCL2ImgWinView::OnUpdateEditSure(CCmdUI *pCmdUI)
{
	bool isEditing = (m_Status == MATCHING); 
	pCmdUI->Enable(isEditing);
}


void CPCL2ImgWinView::SetStatusText(LPCTSTR txt){
 	CMainFrame* pFrame     = (CMainFrame*)::AfxGetMainWnd();
	pFrame->GetStatusBar()->SetPaneText(0,txt); 
}


void CPCL2ImgWinView::OnModify()
{
	// TODO: 在此添加命令处理程序代码
	int nItem = m_CListPointsCtrl->GetNextItem(-1, LVNI_SELECTED);

	if (nItem == -1){
		AfxMessageBox("没有选择需要修改的记录");
		return;
	}
	m_NowSetIndex = nItem; 
	///////////////
	/*m_HasSetCnt--;
	RefreshPointsList();*/
	///////////////
	memcpy(&m_NowEditPoint,&m_SwithPoints[m_NowSetIndex],sizeof(SwitchPoints));

	// TODO: 在此添加命令处理程序代码
	m_Status = MATCHING;
	SetEditStep(0);

	SetStatusText(_T("请在点云中按Shift + 鼠标左键选择点"));
}


void CPCL2ImgWinView::OnUpdateModify(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	bool isEditing = (m_Status == MATCHING);

	pCmdUI->Enable(!isEditing); 
}


/************************************************************************/
/* 计算                                                                     */
/************************************************************************/
void CPCL2ImgWinView::OnCalc()
{

	////////////////////////////
	//INT_PTR nRes;
	//CInit InitDlg;
	//nRes = InitDlg.DoModal();
	///////////////////////////
	GXFC G_solve;
	///////////////////
	double result_R[9];
	for(int i=0;i<9;i++) result_R[i] = 0;
	double result_X = 0;
	double result_Y = 0;
	double result_Z = 0;

	///////////////////初始化
	//for(int i=0;i<5;i++)
	//	G_solve[i].initCanshu();
	G_solve.initCanshu();
	
	int shunxu[5][5]={
		  {0,1,2,3,4},//4
		  {0,1,2,4,3},//3
		  {0,2,3,4,1},//1
		  {0,1,3,4,2},//2
		  {1,2,3,4,0}};//0	

	double temp3d_x;
	double temp3d_y;
	double temp3d_z ;
	double temp2d_x;
	double temp2d_y ;
	
	//int threshold = 50;//设置误差阈值
	int threshold = 10;//设置误差阈值
	//IDD_INIT_DIALOG.vesrion = true;

	if (m_HasSetCnt < 4){
		AfxMessageBox("匹配的点的数量不足");
		return;
	}

	//debug for points cw
	/*ifstream switchPoints_in("switchPoints.txt");
	for (int i=0; i<5; i++)
	{
		switchPoints_in >> m_SwithPoints[i].point3d.x >>  m_SwithPoints[i].point3d.y >> m_SwithPoints[i].point3d.z  >>  m_SwithPoints[i].point2d.x >>  m_SwithPoints[i].point2d.y ;
	}
	switchPoints_in.close();*/

	//保存选择的点对
	/*ofstream switchPoints("switchPoints.txt");
	for (int i=0; i<5; i++)
	{
		switchPoints << m_SwithPoints[i].point3d.x << " "<<m_SwithPoints[i].point3d.y<<" " <<m_SwithPoints[i].point3d.z<<" "
			<<m_SwithPoints[i].point2d.x<<" "<<m_SwithPoints[i].point2d.y<<"\t\n";
	}
	switchPoints.close();
	*////////////////////////////////////////
	//////////////////////////////////////
	
	bool is_true[5]; // 用于保存求解是否正确的标志位
	double sum_wucha[5];
	int min_index = -1; //最小误差对应的序号
	double min_wucha = 100000000000000000; //最小误差的值
	for (int xh=0; xh<5; xh++)//我们一共选取了5个点，任选其中四个点来求得旋转矩阵R，共有5种方式，因此，有必要最多循环5次
	{	
		is_true[xh] = false;
		sum_wucha[xh] = -1;
		for (int i=0; i<4; i++)
		{
			int p_count = shunxu[xh][i];
			temp3d_x = m_SwithPoints[p_count].point3d.x;
			temp3d_y = m_SwithPoints[p_count].point3d.y;
			temp3d_z = m_SwithPoints[p_count].point3d.z;
			temp2d_x = m_SwithPoints[p_count].point2d.x;
			temp2d_y = m_SwithPoints[p_count].point2d.y;
	
			G_solve.B[i][0] = temp2d_x*G_solve.f*0.000001;
			G_solve.B[i][1] = temp2d_y*G_solve.f*0.000001;
			G_solve.B[i][2] = temp3d_x;
			G_solve.B[i][3] = temp3d_y;
			G_solve.B[i][4] = temp3d_z;
		}
			
		is_true[xh] = G_solve.solveR();//所有的数据的初始化，需要我们是输入的数据，都在这个函数里进行初始化//求得矩阵R
		
		if (!is_true[xh])//如果发生问题就不计算误差了
			continue;

		
		/////////////求误差//////////////////
		////////////////////////////////////
		double fk=G_solve.fk; //相机拍摄时的焦距
		double x0 = G_solve.x0;//相机的主点坐标
		double y0 = G_solve.y0;
		double f = G_solve.f;//像素大小，单位为微米
		double Xs = G_solve.Xs;//Xs，Ys，Zs在计算旋转矩阵的时候就已经发生了改变，因此，在下面计算三维点对应的像素坐标时，需要先更新这三个数值
		double Ys = G_solve.Ys;
		double Zs = G_solve.Zs;
		sum_wucha[xh] = 0;		
	
		for (int i=0; i<5; i++)//计算五个点的误差和
		{
			int p_count = shunxu[xh][i];
			temp3d_x = m_SwithPoints[p_count].point3d.x;
			temp3d_y = m_SwithPoints[p_count].point3d.y;
			temp3d_z = m_SwithPoints[p_count].point3d.z;
			temp2d_x = m_SwithPoints[p_count].point2d.x;
			temp2d_y = m_SwithPoints[p_count].point2d.y;
			double x1,y1;
			x1 = x0 - fk*(G_solve.R[0][0]*(temp3d_x-Xs)+G_solve.R[1][0]*(temp3d_y-Ys)+G_solve.R[2][0]*(temp3d_z-Zs)) / ( G_solve.R[0][2]*(temp3d_x-Xs) + G_solve.R[1][2]*(temp3d_y-Ys) + G_solve.R[2][2]*(temp3d_z-Zs));
			y1 = y0 - fk*(G_solve.R[0][1]*(temp3d_x-Xs)+G_solve.R[1][1]*(temp3d_y-Ys)+G_solve.R[2][1]*(temp3d_z-Zs)) / ( G_solve.R[0][2]*(temp3d_x-Xs) + G_solve.R[1][2]*(temp3d_y-Ys) + G_solve.R[2][2]*(temp3d_z-Zs));
			x1 = (x1/f)*1000000;
			y1 = (y1/f)*1000000;
			//此时计算出来的x1，y1就是要求的图像上的像素坐标
			double wucha = sqrt(pow((x1-temp2d_x),2) + pow((y1-temp2d_y),2));
			//errors.push_back(wucha);
			sum_wucha[xh] += wucha;
		}
		//得到最小的误差对应的标号，min_wucha 初始值是1000000000
		if(sum_wucha[xh]<min_wucha)
		{
			min_index = xh;
			min_wucha = sum_wucha[xh];
			for (int ii = 0;ii<9;ii++)
				result_R[ii] = G_solve.R[ii/3][ii%3];
			result_X = G_solve.Xs;
			result_Y = G_solve.Ys;
			result_Z = G_solve.Zs;
		}
	}//计算完毕5组解G_solve[5]，并得到误差 sum_wucha[5]，计算是否正确放在 is_true[5]

	if(min_index<0 || min_index>4 )//不存在成功计算的组合
	{
		MessageBox("case1:五组点都无法计算，请重新选点！");
		return ;
	}else
	{
		CString str;
		str.Format("%lf",min_wucha/5);
		//MessageBox("误差为："+str); //cwang
		MessageBox("最小误差为："+str); //cwang
	}

	//如果有成功处理的就输出，不管误差有多大
	//只要有一组数据符合误差要求，我们就可以认为选择的点有意义，就可以结束误差估算，输出旋转矩阵R
	{
		/////////下面为输出误差值,并保存在wucha.txt文件中///////////////////////////////////
		CString str;
		min_wucha = min_wucha / 5;
		while (min_wucha > 2)
		{
			min_wucha = min_wucha / 2;
		}
				
		str.Format("%.2lf",min_wucha);
		MessageBox("     初始配准精度:\n     为: "+str+"个像素\n"+"     为: "+str+"个激光网格.");
		ofstream save_wucha("wucha.txt");
		save_wucha << "误差为:"<<str<<" ";
		save_wucha.close();
		
		//MessageBox("选点正确");

		///////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////
		//保存旋转矩阵R和计算后的Xs,Ys,Zs
				
		///////////////////////////////////////////////////////////////////////////////////
		///////////旋转矩阵写入临时文件夹中////////
		char tempPath[50];
		DWORD dwSize=50;
		GetTempPath(dwSize,tempPath);
		string temp_path(&tempPath[0],&tempPath[strlen(tempPath)]);

		ofstream f_temp(temp_path+"temp_out.txt");
		if(f_temp){
			for (int i=0;i<9;i++)
				f_temp<<  result_R[i] << " ";
		}
		f_temp <<result_X<<" "<<result_Y<<" "<<result_Z<<" ";
		f_temp.close();	
	}


	TiShi dialog;
	dialog.DoModal();
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}
void CPCL2ImgWinView::OnClose()
{
	CView::OnClose();
}





