
// PCL2ImgWinView.cpp : CPCL2ImgWinView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "PCL2ImgWin.h"
#endif
#include<cstring>
#include "PCL2ImgWinDoc.h"
#include "PCL2ImgWinView.h"
#include "MainFrm.h"
#include "GXFC.h"

#include "Init.h"//������ʼ���Ի����ͷ�ļ�
#include "TiShi.h"
#include <iomanip>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPCL2ImgWinView

IMPLEMENT_DYNCREATE(CPCL2ImgWinView, CView)

BEGIN_MESSAGE_MAP(CPCL2ImgWinView, CView)
	// ��׼��ӡ����
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

// CPCL2ImgWinView ����/����

CPCL2ImgWinView::CPCL2ImgWinView() 
{
	// TODO: �ڴ˴���ӹ������
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
	bitmap.Detach (); //�ڼ���ǰ���ͷ�λͼ

	bitmap.LoadBitmap(IDB_BITMAP2);
	m_ImgList.Add (&bitmap,RGB(0,0,0));
	bitmap.Detach (); //�ڼ���ǰ���ͷ�λͼ

	bitmap.LoadBitmap(IDB_BITMAP3);
	m_ImgList.Add (&bitmap,RGB(0,0,0));
	bitmap.Detach (); //�ڼ���ǰ���ͷ�λͼ

	bitmap.LoadBitmap(IDB_BITMAP4);
	m_ImgList.Add (&bitmap,RGB(0,0,0));
	bitmap.Detach (); //�ڼ���ǰ���ͷ�λͼ

	bitmap.LoadBitmap(IDB_BITMAP5);
	m_ImgList.Add (&bitmap,RGB(0,0,0));
	bitmap.Detach (); //�ڼ���ǰ���ͷ�λͼ

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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPCL2ImgWinView ����

void CPCL2ImgWinView::OnDraw(CDC* /*pDC*/)
{
	CPCL2ImgWinDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}
 

BOOL CPCL2ImgWinView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPCL2ImgWinView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPCL2ImgWinView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CPCL2ImgWinView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPCL2ImgWinView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{ 
}


// CPCL2ImgWinView ���

#ifdef _DEBUG
void CPCL2ImgWinView::AssertValid() const
{
	CView::AssertValid();
}

void CPCL2ImgWinView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPCL2ImgWinDoc* CPCL2ImgWinView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCL2ImgWinDoc)));
	return (CPCL2ImgWinDoc*)m_pDocument;
}
#endif //_DEBUG


// CPCL2ImgWinView ��Ϣ�������
void CPCL2ImgWinView::OnInitialUpdate()
{
	
	GetParentFrame()->RecalcLayout();

	//�Զ����ŵ���ǰ���ڵĴ�С������С
    //SetScaleToFitSize(m_sizeView);

	//ȡ��Ĭ�������
	CRect rect;
	GetClientRect( &rect );
	rect.DeflateRect(20,20); 
 
	m_PclCtrl = new CPCLDlg();
	m_PclCtrl->CreateEx(NULL,NULL, "PCL",WS_CHILD|WS_VISIBLE, rect, this, IDC_PCL, NULL);  
	m_PclCtrl->ShowWindow(SW_SHOW);/*
	m_PclCtrl->ReadLasFile("F:\\Projects\\��\\2015715�״���\\project2015713\\project2015713\\sh.las");*/

	m_ProjInfoCtrl = new CProjectInfoDlg();
	m_ProjInfoCtrl->CreateEx(NULL,NULL, "PROJINFO",WS_CHILD|WS_VISIBLE, rect, this, IDC_NAVIGATION, NULL); 

    m_ImgCtrl = new CImgDlg();
	m_ImgCtrl->CreateEx(NULL,NULL, "IMG",WS_CHILD|WS_VISIBLE, rect, this, IDC_IMG, NULL);
    m_ImgCtrl->OnInit();
    //��
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
		AfxMessageBox(_T("���ֻ��Ҫ5�Ե㣡"));
		return;
	}

	m_NowSetIndex = m_HasSetCnt; 
	memset(&m_NowEditPoint,NULL,sizeof(SwitchPoints));

	// TODO: �ڴ���������������
	m_Status = MATCHING;
	SetEditStep(0);

	SetStatusText(_T("���ڰ�Shift + ����������ͼ��ѡ��㣡"));
}


void CPCL2ImgWinView::OnUpdateSetSwitchpoint(CCmdUI *pCmdUI)
{ 
	bool isEditing = (m_Status == MATCHING);

	pCmdUI->Enable(!isEditing); 
}

void CPCL2ImgWinView::SetEditStep(int step){
	if (m_EditStep < step)
		m_EditStep = step; 
    SetStatusText(_T("���ڰ�Shift + ����������ͼ��ѡ��㣡"));
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
		 SetStatusText(_T("�����ڵ�����ѡ���"));
		 return;
	}

	if (m_EditStep == 1){
		SetStatusText(_T("����ң��ͼ����ѡ���"));
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
	// TODO: �ڴ���������������
	int nItem = m_CListPointsCtrl->GetNextItem(-1, LVNI_SELECTED);

	if (nItem == -1){
		AfxMessageBox("û��ѡ����Ҫ�޸ĵļ�¼");
		return;
	}
	m_NowSetIndex = nItem; 
	///////////////
	/*m_HasSetCnt--;
	RefreshPointsList();*/
	///////////////
	memcpy(&m_NowEditPoint,&m_SwithPoints[m_NowSetIndex],sizeof(SwitchPoints));

	// TODO: �ڴ���������������
	m_Status = MATCHING;
	SetEditStep(0);

	SetStatusText(_T("���ڵ����а�Shift + ������ѡ���"));
}


void CPCL2ImgWinView::OnUpdateModify(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	bool isEditing = (m_Status == MATCHING);

	pCmdUI->Enable(!isEditing); 
}


/************************************************************************/
/* ����                                                                     */
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

	///////////////////��ʼ��
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
	
	//int threshold = 50;//���������ֵ
	int threshold = 10;//���������ֵ
	//IDD_INIT_DIALOG.vesrion = true;

	if (m_HasSetCnt < 4){
		AfxMessageBox("ƥ��ĵ����������");
		return;
	}

	//debug for points cw
	/*ifstream switchPoints_in("switchPoints.txt");
	for (int i=0; i<5; i++)
	{
		switchPoints_in >> m_SwithPoints[i].point3d.x >>  m_SwithPoints[i].point3d.y >> m_SwithPoints[i].point3d.z  >>  m_SwithPoints[i].point2d.x >>  m_SwithPoints[i].point2d.y ;
	}
	switchPoints_in.close();*/

	//����ѡ��ĵ��
	/*ofstream switchPoints("switchPoints.txt");
	for (int i=0; i<5; i++)
	{
		switchPoints << m_SwithPoints[i].point3d.x << " "<<m_SwithPoints[i].point3d.y<<" " <<m_SwithPoints[i].point3d.z<<" "
			<<m_SwithPoints[i].point2d.x<<" "<<m_SwithPoints[i].point2d.y<<"\t\n";
	}
	switchPoints.close();
	*////////////////////////////////////////
	//////////////////////////////////////
	
	bool is_true[5]; // ���ڱ�������Ƿ���ȷ�ı�־λ
	double sum_wucha[5];
	int min_index = -1; //��С����Ӧ�����
	double min_wucha = 100000000000000000; //��С����ֵ
	for (int xh=0; xh<5; xh++)//����һ��ѡȡ��5���㣬��ѡ�����ĸ����������ת����R������5�ַ�ʽ����ˣ��б�Ҫ���ѭ��5��
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
			
		is_true[xh] = G_solve.solveR();//���е����ݵĳ�ʼ������Ҫ��������������ݣ����������������г�ʼ��//��þ���R
		
		if (!is_true[xh])//�����������Ͳ����������
			continue;

		
		/////////////�����//////////////////
		////////////////////////////////////
		double fk=G_solve.fk; //�������ʱ�Ľ���
		double x0 = G_solve.x0;//�������������
		double y0 = G_solve.y0;
		double f = G_solve.f;//���ش�С����λΪ΢��
		double Xs = G_solve.Xs;//Xs��Ys��Zs�ڼ�����ת�����ʱ����Ѿ������˸ı䣬��ˣ������������ά���Ӧ����������ʱ����Ҫ�ȸ�����������ֵ
		double Ys = G_solve.Ys;
		double Zs = G_solve.Zs;
		sum_wucha[xh] = 0;		
	
		for (int i=0; i<5; i++)//��������������
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
			//��ʱ���������x1��y1����Ҫ���ͼ���ϵ���������
			double wucha = sqrt(pow((x1-temp2d_x),2) + pow((y1-temp2d_y),2));
			//errors.push_back(wucha);
			sum_wucha[xh] += wucha;
		}
		//�õ���С������Ӧ�ı�ţ�min_wucha ��ʼֵ��1000000000
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
	}//�������5���G_solve[5]�����õ���� sum_wucha[5]�������Ƿ���ȷ���� is_true[5]

	if(min_index<0 || min_index>4 )//�����ڳɹ���������
	{
		MessageBox("case1:����㶼�޷����㣬������ѡ�㣡");
		return ;
	}else
	{
		CString str;
		str.Format("%lf",min_wucha/5);
		//MessageBox("���Ϊ��"+str); //cwang
		MessageBox("��С���Ϊ��"+str); //cwang
	}

	//����гɹ�����ľ��������������ж��
	//ֻҪ��һ�����ݷ������Ҫ�����ǾͿ�����Ϊѡ��ĵ������壬�Ϳ��Խ��������㣬�����ת����R
	{
		/////////����Ϊ������ֵ,��������wucha.txt�ļ���///////////////////////////////////
		CString str;
		min_wucha = min_wucha / 5;
		while (min_wucha > 2)
		{
			min_wucha = min_wucha / 2;
		}
				
		str.Format("%.2lf",min_wucha);
		MessageBox("     ��ʼ��׼����:\n     Ϊ: "+str+"������\n"+"     Ϊ: "+str+"����������.");
		ofstream save_wucha("wucha.txt");
		save_wucha << "���Ϊ:"<<str<<" ";
		save_wucha.close();
		
		//MessageBox("ѡ����ȷ");

		///////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////
		//������ת����R�ͼ�����Xs,Ys,Zs
				
		///////////////////////////////////////////////////////////////////////////////////
		///////////��ת����д����ʱ�ļ�����////////
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





