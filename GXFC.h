#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
#include "PCL2ImgWinView.h"

#include "Init.h"//包含初始化对话框的头文件
using namespace std;

const int n=6;
//void inverse (double c[n][n]);
//
//template<typename T>void input (T*mat,int a,int b);
//template<typename T>void output(T*mat,char*s,int a,int b);

class GXFC{
public:
	double B[4][5];
	double R[3][3];
	
	double x0,y0,fk,Xs,Ys,Zs,Q,W,K,f,m;
	int xh;
	bool solveR();
	template<typename T1,typename T2>void transpose (T1*mat1,T2*mat2,int a,int b);
    template<typename T1,typename T2>void multi(T1*mat1,T2 * mat2,T2 * result,int a,int b,int c);
    void inverse (double c[n][n]);
    bool wucha();
	void initCanshu();
};

void GXFC::initCanshu()
{

	////////////////////////////
	INT_PTR nRes;
	CInit InitDlg;
	nRes = InitDlg.DoModal();
	///////////////////////////
	 x0=InitDlg.m_X0;;
	 y0=InitDlg.m_Y0;;   //内方位元素
	 fk=InitDlg.m_fk;
	 Xs=InitDlg.m_Xs;
	 Ys=InitDlg.m_Ys;
	 Zs=InitDlg.m_Zs;
	 Q=InitDlg.m_Q;
	 W=InitDlg.m_W;
	 K=InitDlg.m_K;//外方位元素
	 f = InitDlg.m_f;
	 m = InitDlg.m_m;
	 return ;
}

void GXFC::inverse(double c[n][n])
{  int i,j,h,k;
double p;
double q[n][12];
for(i=0;i<n;i++)//构造高斯矩阵
	for(j=0;j<n;j++)
		q[i][j]=c[i][j];
for(i=0;i<n;i++)
	for(j=n;j<12;j++)
	{if(i+6==j)
	q[i][j]=1;
	else
		q[i][j]=0;}
	for(h=k=0;k<n-1;k++,h++)//消去对角线以下的数据
		for(i=k+1;i<n;i++)
		{if(q[i][h]==0)
		continue;
	p=q[k][h]/q[i][h];
	for(j=0;j<12;j++)
	{ q[i][j]*=p;
	q[i][j]-=q[k][j];
	}
		}
		for(h=k=n-1;k>0;k--,h--) // 消去对角线以上的数据
			for(i=k-1;i>=0;i--)
			{if(q[i][h]==0)
			continue;
		p=q[k][h]/q[i][h];
		for(j=0;j<12;j++)
		{q[i][j]*=p;
		q[i][j]-=q[k][j];}}
			for(i=0;i<n;i++)//将对角线上数据化为1
			{ p=1.0/q[i][i];
			for(j=0;j<12;j++)
				q[i][j]*=p;}
			for(i=0;i<n;i++) //提取逆矩阵
				for(j=0;j<n;j++)
					c[i][j]=q[i][j+6];
			}

template<typename T1,typename T2>void GXFC::transpose(T1*mat1,T2*mat2,int a,int b)
{  int i,j;
for(i=0;i<b;i++)
	for(j=0;j<a;j++)
		mat2[j][i]=mat1[i][j];
return;
}

template<typename T1,typename T2>void GXFC::multi(T1*mat1,T2 * mat2,T2 * result,int a,int b,int c)
{   int i,j,k;
for(i=0;i<a;i++)
	{for(j=0;j<c;j++)
		{result[i][j]=0;
		for(k=0;k<b;k++)
			result[i][j]+=mat1[i][k]*mat2[k][j];
		}
	}
return;
}

bool GXFC::solveR()
{
	int i,j,k;
	 //x0=0.0;
	 //y0=0.0;   //内方位元素
	 //fk=0.053; 
	 //Xs=80148.543;
	 //Ys=1788549.170;
	 //Zs=5375.949;
	 //Q=-0.44155;
	 //W=-3.24751;
	 //K=-94.45164;//外方位元素
	 //f = 5.2;
	 

	//double m=39689;  //估算比例尺
	//double m=65000;


	double XG[6][1],AT[6][8],ATA[6][6],ATL[6][1];
	
	double X,Y,Z,L[8][1],A[8][6]; 
	//确定未知数的出始值
	for(int i=0;i<4;i++)
	{Xs=Xs+B[i][2];
	Ys=Ys+B[i][3];
	Zs=Zs+B[i][4];
	}
	Xs=Xs/4; Ys=Ys/4; Zs=Zs/4+m*fk;
	int f=0;
	do//迭代计算
	{f++;
	//组成旋转矩阵
	R[0][0]=cos(Q)*cos(K)-sin(Q)*sin(W)*sin(K);
	R[0][1]=-cos(Q)*sin(K)-sin(Q)*sin(W)*cos(K);
	R[0][2]=-sin(Q)*cos(W);
	R[1][0]=cos(W)*sin(K);
	R[1][1]=cos(W)*cos(K);
	R[1][2]=-sin(W);
	R[2][0]=sin(Q)*cos(K)+cos(Q)*sin(W)*sin(K);
	R[2][1]=-sin(Q)*sin(K)+cos(Q)*sin(W)*cos(K);
	R[2][2]=cos(Q)*cos(W);
	//计算系数阵和常数项
	for(i=0,k=0,j=0;i<=3;i++,k++,j++)
	{
		X=R[0][0]*(B[i][2]-Xs)+R[1][0]*(B[i][3]-Ys)+R[2][0]*(B[i][4]-Zs);
		Y=R[0][1]*(B[i][2]-Xs)+R[1][1]*(B[i][3]-Ys)+R[2][1]*(B[i][4]-Zs);
		Z=R[0][2]*(B[i][2]-Xs)+R[1][2]*(B[i][3]-Ys)+R[2][2]*(B[i][4]-Zs);
		////////////////////
		////////////////////
		if (Z == 0)
		{
			return false;
		}
		///////////////////////
		///////////////////////
		L[j][0]=B[i][0]-(x0-fk*X/Z);
		L[j+1][0]=B[i][1]-(y0-fk*Y/Z);
		j++;
		A[k][0]=(R[0][0]*fk+R[0][2]*(B[i][0]-x0))/Z;
		A[k][1]=(R[1][0]*fk+R[1][2]*(B[i][0]-x0))/Z;
		A[k][2]=(R[2][0]*fk+R[2][2]*(B[i][0]-x0))/Z;
		A[k][3]=(B[i][1]-y0)*sin(W)-((B[i][0]-x0)*((B[i][0]-x0)*cos(K)-(B[i][1]-y0)*sin(K))/fk+fk*cos(K))*cos(W);
		A[k][4]=-fk*sin(K)-(B[i][0]-x0)*((B[i][0]-x0)*sin(K)+(B[i][1]-y0)*cos(K))/fk;
		A[k][5]=B[i][1]-y0;
		A[k+1][0]=(R[0][1]*fk+R[0][2]*(B[i][1]-y0))/Z;
		A[k+1][1]=(R[1][1]*fk+R[1][2]*(B[i][1]-y0))/Z;
		A[k+1][2]=(R[2][1]*fk+R[2][2]*(B[i][1]-y0))/Z;
		A[k+1][3]=-(B[i][0]-x0)*sin(W)-((B[i][1]-y0)*((B[i][0]-x0)*cos(K)-(B[i][1]-y0)*sin(K))/fk-fk*sin(K))*cos(W);
		A[k+1][4]=-fk*cos(K)-(B[i][1]-y0)*((B[i][0]-x0)*sin(K)+(B[i][1]-y0)*cos(K))/fk;
		A[k+1][5]=-(B[i][0]-x0);
		k++;
	}
	transpose(A,AT,6,8);
	multi(AT,A,ATA,6,8,6);
	inverse(ATA);
	multi(AT,L,ATL,6,8,1);
	multi(ATA,ATL,XG,6,6,1);
	Xs=Xs+XG[0][0]; Ys=Ys+XG[1][0]; Zs=Zs+XG[2][0];
	Q=Q+XG[3][0];  W=W+XG[4][0];  K=K+XG[5][0];
	}while(XG[3][0]>=6.0/206265.0||XG[4][0]>=6.0/206265.0||XG[5][0]>=6.0/206265.0);

	return true;

}

