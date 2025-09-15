
// WSCADDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "WSCAD.h"
#include "WSCADDlg.h"
#include "afxdialogex.h"
#include "math.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v23 Study\SDK\Include\ksConstants.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v23 Study\SDK\Include\ksConstants3D.h"
//#include "C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\kapi5.h"
#include <atlsafe.h>
//#include <C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\Ks_TLB.h>

#include <comutil.h>



#define PI 4*atan(1)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma once


#import "C:\Program Files\ASCON\KOMPAS-3D v23 Study\SDK\lib\kAPI5.tlb"



using namespace Kompas6API5;
//using namespace KompasAPI5;


KompasObjectPtr pKompasApp5;
//KompasObjectPtr pKompasApp5;

ksPartPtr pPart;// = PartDoc->GetTopPart();
ksDocument3DPtr pDoc;



// ���������� ���� CWSCADDlg



CWSCADDlg::CWSCADDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_WSCAD_DIALOG, pParent)
	, m_Width(120)
	, m_Depth(40)
	, m_Height(75)
	, m_lFaskaAll(5)		//��� ����� 90
	, m_hDna(15)
	, m_dHoleSmall(5)
	, m_dZenk(15)			//��� ����� 90
	, m_lInterHole(80)
	, m_rRound(15)
	, m_WidthTower(50)
	, m_lCek(15)
	, m_dCek(35)
	, m_dHoleBig(15)
	, m_hToHole(50)
	, m_lFaskaTower(15)		//��� ����� 45	
	, m_dHoleUpper(7.5)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWSCADDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_Width);
	DDV_MinMaxDouble(pDX, m_Width, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_DEPTH, m_Depth);
	DDV_MinMaxInt(pDX, m_Depth, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_Height);
	DDV_MinMaxDouble(pDX, m_Height, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_L_FASKA_ALL, m_lFaskaAll);
	DDV_MinMaxDouble(pDX, m_lFaskaAll, 0, 10000);

	DDX_Text(pDX, IDC_EDIT_H_PODDONA, m_hDna);
	DDV_MinMaxDouble(pDX, m_hDna, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_D_HOLE_SMALL, m_dHoleSmall);
	DDV_MinMaxDouble(pDX, m_dHoleSmall, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_D_ZENK, m_dZenk);
	DDV_MinMaxDouble(pDX, m_dZenk, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_L_INTER_HOLE, m_lInterHole);	//���������� ����� ����������� � ���
	DDV_MinMaxDouble(pDX, m_lInterHole, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_R_ROUNDING_CORNERS, m_rRound);	//������ ���������� ����� ���
	DDV_MinMaxDouble(pDX, m_rRound, 0, 10000);

	DDX_Text(pDX, IDC_EDIT_W_TOWER, m_WidthTower);
	DDV_MinMaxDouble(pDX, m_WidthTower, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_L_CEK, m_lCek);			//������� ��������
	DDV_MinMaxDouble(pDX, m_lCek, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_D_CEK, m_dCek);
	DDV_MinMaxDouble(pDX, m_dCek, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_D_HOLE_BIG, m_dHoleBig);
	DDV_MinMaxDouble(pDX, m_dHoleBig, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_H_TO_HOLE, m_hToHole);		//������ �� ������ ��������� � �����
	DDV_MinMaxDouble(pDX, m_hToHole, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_L_FASKA_TOWER, m_lFaskaTower);
	DDV_MinMaxDouble(pDX, m_lFaskaTower, 0, 10000);
	DDX_Text(pDX, IDC_EDIT_D_HOLE_UPPER, m_dHoleUpper);
	DDV_MinMaxDouble(pDX, m_dHoleUpper, 0, 10000);
}

BEGIN_MESSAGE_MAP(CWSCADDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BUILD, &CWSCADDlg::OnBnClickedButtonBuild)
	ON_BN_CLICKED(IDOK, &CWSCADDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ����������� ��������� CWSCADDlg

BOOL CWSCADDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����.  ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������.  ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CWSCADDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CWSCADDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CWSCADDlg::CheckData()
{
	if (!UpdateData())
		return false;

	 return true;
}


void CWSCADDlg::OnBnClickedOk()
{
	// TODO: �������� ���� ��� ����������� �����������
	//if (pInvApp)
	//    pInvApp->MethodQuit();
 //   
	CDialog::OnOK();
}


//IKompasDocument3DPtr PartDoc;
void CWSCADDlg::OnBnClickedButtonBuild()
{
	// TODO: �������� ���� ��� ����������� �����������
	BeginWaitCursor();

	if (!CheckData())
		return;

	CComPtr<IUnknown> pKompasAppUnk = nullptr;
	if (!pKompasApp5)
	{
		// �������� CLSID ��� ������
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp5 = nullptr;
			return;
		}

		// ��������� ���� �� ���������� ��������� ������
		//���� ���� �������� IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// ���������� ��������� ������ ����� ��� ��� ����������� ���
			// ����� �������� IUnknown ��� ������ ��� ����������� ���������� ������
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				pKompasApp5 = nullptr;
				return;
			}
		}

		// �������� ��������� ���������� ������
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}
	}

	// ������ ������ �������
	pKompasApp5->Visible = true;
	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pPart = pDoc->GetPart(pTop_Part);

	//������ ������
	ksEntityPtr pSketch = pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef = pSketch->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pSketch->Create();
	ksDocument2DPtr p2DDoc = pSketchDef->BeginEdit();

	//������������� � ������������� ������, ����� �� �������
	double point[8][2];		//x � y ��� ������
	double centers[4][2];	//x � y ������� ����������
	point[0][0] = m_Width / 2.f - m_rRound;	//���� ���� ����
	point[0][1] = m_Depth / 2.f;
	point[1][0] = m_Width / 2.f;
	point[1][1] = m_Depth / 2.f - m_rRound;
	point[2][0] = m_Width / 2.f;				//���� ��� ����
	point[2][1] = -(m_Depth / 2.f - m_rRound);
	point[3][0] = m_Width / 2.f - m_rRound;
	point[3][1] = -m_Depth / 2.f;
	point[4][0] = -(m_Width / 2.f - m_rRound);	//��� ��� ����
	point[4][1] = -m_Depth / 2.f;
	point[5][0] = -m_Width / 2.f;
	point[5][1] = -(m_Depth / 2.f - m_rRound);
	point[6][0] = -m_Width / 2.f;					//��� ���� ����
	point[6][1] = m_Depth / 2.f - m_rRound;
	point[7][0] = -(m_Width / 2.f - m_rRound);
	point[7][1] = m_Depth / 2.f;
	p2DDoc->ksLineSeg(point[7][0], point[7][1], point[0][0], point[0][1], 1);
	p2DDoc->ksLineSeg(point[1][0], point[1][1], point[2][0], point[2][1], 1);
	p2DDoc->ksLineSeg(point[3][0], point[3][1], point[4][0], point[4][1], 1);
	p2DDoc->ksLineSeg(point[5][0], point[5][1], point[6][0], point[6][1], 1);

	centers[0][0] = m_Width / 2.f - m_rRound;
	centers[0][1] = m_Depth / 2.f - m_rRound;
	centers[1][0] = m_Width / 2.f - m_rRound;
	centers[1][1] = -(m_Depth / 2.f - m_rRound);
	centers[2][0] = -(m_Width / 2.f - m_rRound);
	centers[2][1] = -(m_Depth / 2.f - m_rRound);
	centers[3][0] = -(m_Width / 2.f - m_rRound);
	centers[3][1] = m_Depth / 2.f - m_rRound;
	p2DDoc->ksArcByPoint(centers[0][0], centers[0][1], m_rRound, point[1][0], point[1][1], point[0][0], point[0][1], true, 1);	//�� ��� ������ ������������� ��� direction, �� true �� ���������
	p2DDoc->ksArcByPoint(centers[1][0], centers[1][1], m_rRound, point[3][0], point[3][1], point[2][0], point[2][1], true, 1);	//��, ����� ���������� ���� ������� ��� ���������, ������� �� ������� ����� ������ ����
	p2DDoc->ksArcByPoint(centers[2][0], centers[2][1], m_rRound, point[5][0], point[5][1], point[4][0], point[4][1], true, 1);
	p2DDoc->ksArcByPoint(centers[3][0], centers[3][1], m_rRound, point[7][0], point[7][1], point[6][0], point[6][1], true, 1);

	pSketchDef->EndEdit();


	ksEntityPtr pExtrude = pPart->NewEntity(o3d_bossExtrusion);	//������������ ��������������
	ksBossExtrusionDefinitionPtr pExDef;
	pExDef = pExtrude->GetDefinition();
	pExDef->directionType = dtNormal;
	pExDef->SetSketch(pSketch);
	pExDef->SetSideParam(true, etBlind, m_hDna, 0, false);
	pExDef->SetSideParam(false, etBlind, m_hDna, 0, false);		//side1 ��� ����������� ������������
	pExtrude->Create();

	//������ �����
	ksEntityPtr pSketch1 = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketch1->GetDefinition();		//���������� ���� ��������� �����
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
	pSketch1->Create();
	p2DDoc = pSketchDef->BeginEdit();		//���������� ���� ��������� �����

	double point1[6][2];		//x � y 	//��� �����, ������� ���������, ����� ������ �������
	point1[0][0] = -m_WidthTower / 2.f;
	point1[0][1] = 0;
	point1[1][0] = m_WidthTower / 2.f;
	point1[1][1] = 0;
	point1[2][0] = m_WidthTower / 2.f;
	point1[2][1] = m_Height - m_lFaskaTower;
	point1[3][0] = m_WidthTower / 2.f - m_lFaskaTower;
	point1[3][1] = m_Height;
	point1[4][0] = -(m_WidthTower / 2.f - m_lFaskaTower);
	point1[4][1] = m_Height;
	point1[5][0] = -m_WidthTower / 2.f;
	point1[5][1] = m_Height - m_lFaskaTower;
	for (int i = 0; i < 6; i++) { point1[i][1] *= -1; }
	p2DDoc->ksLineSeg(point1[0][0], point1[0][1], point1[1][0], point1[1][1], 1);
	p2DDoc->ksLineSeg(point1[1][0], point1[1][1], point1[2][0], point1[2][1], 1);
	p2DDoc->ksLineSeg(point1[2][0], point1[2][1], point1[3][0], point1[3][1], 1);
	p2DDoc->ksLineSeg(point1[3][0], point1[3][1], point1[4][0], point1[4][1], 1);
	p2DDoc->ksLineSeg(point1[4][0], point1[4][1], point1[5][0], point1[5][1], 1);
	p2DDoc->ksLineSeg(point1[5][0], point1[5][1], point1[0][0], point1[0][1], 1);
	pSketchDef->EndEdit();

	ksEntityPtr pExtrude1 = pPart->NewEntity(o3d_bossExtrusion);	//������������ ��������������
	pExDef = pExtrude1->GetDefinition();		//���������� ���� ��������� �����
	pExDef->directionType = dtBoth;			//dtNormal ��� � ���� �������
	pExDef->SetSketch(pSketch1);
	pExDef->SetSideParam(true, etBlind, m_Depth / 2.f, 0, false);
	pExDef->SetSideParam(false, etBlind, m_Depth / 2.f, 0, false);
	pExtrude1->Create();

	//������ �����
	ksEntityPtr filletEntity = pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr filletDef = filletEntity->GetDefinition();

	filletDef->SetChamferParam(TRUE, m_lFaskaAll, m_lFaskaAll);
	ksEntityCollectionPtr EdgeCollection = filletDef->array();	//������ ������ ����
	EdgeCollection->Clear();
	ksEntityCollectionPtr edges = pPart->EntityCollection(o3d_edge);	//���� �����
	edges->SelectByPoint(0, -m_Depth / 2.f, m_Height);
	EdgeCollection->Add(edges->GetByIndex(0));
	edges = pPart->EntityCollection(o3d_edge);
	edges->SelectByPoint(m_WidthTower / 2.f, -m_Depth / 2.f, m_hDna + 1);			//������� ���� �����
	EdgeCollection->Add(edges->GetByIndex(0));
	edges = pPart->EntityCollection(o3d_edge);
	edges->SelectByPoint(-m_WidthTower / 2.f, -m_Depth / 2.f, m_hDna + 1);
	EdgeCollection->Add(edges->GetByIndex(0));
	edges = pPart->EntityCollection(o3d_edge);							//����� �����
	edges->SelectByPoint(m_WidthTower / 2.f - m_lFaskaTower / 2.f, -m_Depth / 2.f, m_Height - m_lFaskaTower / 2.f);
	EdgeCollection->Add(edges->GetByIndex(0));
	edges = pPart->EntityCollection(o3d_edge);
	edges->SelectByPoint(-(m_WidthTower / 2.f - m_lFaskaTower / 2.f), -m_Depth / 2.f, m_Height - m_lFaskaTower / 2.f);
	EdgeCollection->Add(edges->GetByIndex(0));
	edges = pPart->EntityCollection(o3d_edge);							//������
	edges->SelectByPoint(m_Width / 2.f, 0, m_hDna);
	EdgeCollection->Add(edges->GetByIndex(0));
	edges = pPart->EntityCollection(o3d_edge);
	edges->SelectByPoint(-m_Width / 2.f, 0, m_hDna);
	EdgeCollection->Add(edges->GetByIndex(0));
	edges = pPart->EntityCollection(o3d_edge);							//����� �������� � ������
	edges->SelectByPoint(m_WidthTower / 2.f, 0, m_hDna);
	EdgeCollection->Add(edges->GetByIndex(0));
	edges = pPart->EntityCollection(o3d_edge);
	edges->SelectByPoint(-m_WidthTower / 2.f, 0, m_hDna);
	EdgeCollection->Add(edges->GetByIndex(0));

	filletEntity->Create();

	//������ ����� ��������� ������
	ksEntityPtr pPlaneHoleUpper = pPart->NewEntity(o3d_planeOffset);			//������� ��������� ��������� ����������
	ksPlaneOffsetDefinitionPtr pPlaneDef = pPlaneHoleUpper->GetDefinition();	//������� ��������� ��������� �����
	pPlaneDef->direction = true;
	pPlaneDef->offset = m_Height;
	pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pPlaneHoleUpper->Create();

	ksEntityPtr pSketchHoleUpper = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchHoleUpper->GetDefinition();
	pSketchDef->SetPlane(pPlaneHoleUpper);
	pSketchHoleUpper->Create();

	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksCircle(0, 0, m_dHoleUpper / 2.f, 1);	//� ���� ���������� ��������, � �������� �������
	pSketchDef->EndEdit();

	ksEntityPtr pExtrudeHoleUpper = pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr pExDefCut = pExtrudeHoleUpper->GetDefinition();		//������ ������ ���������
	pExDefCut->directionType = dtNormal;
	pExDefCut->SetSketch(pSketchHoleUpper);
	pExDefCut->SetSideParam(true, etBlind, m_Height - m_hToHole, 0, false);
	pExtrudeHoleUpper->Create();


	//����� �������� ���������
	ksEntityPtr pSketchHoleBig = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchHoleBig->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
	pSketchHoleBig->Create();

	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksCircle(0, -m_hToHole, m_dHoleBig / 2.f, 1);	//� ���� ���������� ��������, � �������� �������
	pSketchDef->EndEdit();

	ksEntityPtr pExtrudeHoleBig = pPart->NewEntity(o3d_cutExtrusion);
	pExDefCut = pExtrudeHoleBig->GetDefinition();		//��� ���� �������
	pExDefCut->directionType = dtBoth;
	pExDefCut->SetSketch(pSketchHoleBig);
	pExDefCut->SetSideParam(true, etBlind, m_Depth, 0, false);
	pExDefCut->SetSideParam(false, etBlind, m_Depth, 0, false);
	pExtrudeHoleBig->Create();


	//������ ����� �������
	ksEntityPtr pPlaneHoleCek = pPart->NewEntity(o3d_planeOffset);			//������� ��������� ��������� ����������
	pPlaneDef = pPlaneHoleCek->GetDefinition();		//���������� ���� ��������� �� �����
	pPlaneDef->direction = true;
	pPlaneDef->offset = m_Depth / 2.f;
	pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
	pPlaneHoleCek->Create();

	ksEntityPtr pSketchHoleCek = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchHoleCek->GetDefinition();
	pSketchDef->SetPlane(pPlaneHoleCek);
	pSketchHoleCek->Create();

	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksCircle(0, -m_hToHole, m_dCek / 2.f, 1);	//� ���� ���������� ��������, � �������� �������
	pSketchDef->EndEdit();

	ksEntityPtr pExtrudeHoleCek = pPart->NewEntity(o3d_cutExtrusion);
	pExDefCut = pExtrudeHoleCek->GetDefinition();		//������ ��������� ��� ���� ���������
	pExDefCut->directionType = dtNormal;
	pExDefCut->SetSketch(pSketchHoleCek);
	pExDefCut->SetSideParam(true, etBlind, m_lCek, 0, false);
	pExtrudeHoleCek->Create();



	//������ ����� �������� �� �������
	ksEntityPtr pPlaneHoleZenkUp = pPart->NewEntity(o3d_planeOffset);			//������� ��������� ��������� ����������
	pPlaneDef = pPlaneHoleZenkUp->GetDefinition();		//���������� ���� ��������� �� �����
	pPlaneDef->direction = true;
	pPlaneDef->offset = m_hDna;
	pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pPlaneHoleZenkUp->Create();

	ksEntityPtr pSketchHoleZenkUp = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchHoleZenkUp->GetDefinition();
	pSketchDef->SetPlane(pPlaneHoleZenkUp);
	pSketchHoleZenkUp->Create();

	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksCircle(m_lInterHole / 2.f, 0, m_dZenk / 2.f, 1);	//� ���� ���������� ��������, � �������� �������
	pSketchDef->EndEdit();


	ksEntityPtr pPlaneHoleZenkDown = pPart->NewEntity(o3d_planeOffset);			//������� ��������� ��������� ����������
	pPlaneDef = pPlaneHoleZenkDown->GetDefinition();		//���������� ���� ��������� �� �����
	pPlaneDef->direction = true;
	pPlaneDef->offset = m_hDna - (m_dZenk - m_dHoleSmall) / 2.f;
	pPlaneDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pPlaneHoleZenkDown->Create();

	ksEntityPtr pSketchHoleZenkDown = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchHoleZenkDown->GetDefinition();
	pSketchDef->SetPlane(pPlaneHoleZenkDown);
	pSketchHoleZenkDown->Create();

	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksCircle(m_lInterHole / 2.f, 0, m_dHoleSmall / 2.f, 1);	//� ���� ���������� ��������, � �������� �������
	pSketchDef->EndEdit();


	ksEntityPtr pExtrudeZenk = pPart->NewEntity(o3d_cutLoft);
	ksCutLoftDefinitionPtr pCutLoftDef = pExtrudeZenk->GetDefinition();		//��� ���� �������
	ksEntityCollectionPtr SketchCollection = pCutLoftDef->Sketchs();
	SketchCollection->Clear();
	SketchCollection->Add(pSketchHoleZenkUp);
	SketchCollection->Add(pSketchHoleZenkDown);
	pCutLoftDef->SetLoftParam(FALSE, TRUE, TRUE);
	pExtrudeZenk->Create();


	//������ ����� ������ ���������
	ksEntityPtr pSketchHoleSmall = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketchHoleSmall->GetDefinition();
	pSketchDef->SetPlane(pPlaneHoleZenkUp);
	pSketchHoleSmall->Create();

	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksCircle(m_lInterHole / 2.f, 0, m_dHoleSmall / 2.f, 1);	//� ���� ���������� ��������, � �������� �������
	pSketchDef->EndEdit();

	ksEntityPtr pExtrudeHoleSmall = pPart->NewEntity(o3d_cutExtrusion);
	pExDefCut = pExtrudeHoleSmall->GetDefinition();		//������ ��������� ��� ���� ���������
	pExDefCut->directionType = dtNormal;
	pExDefCut->SetSketch(pSketchHoleSmall);
	pExDefCut->SetSideParam(true, etBlind, m_hDna, 0, false);
	pExtrudeHoleSmall->Create();


	//��������������
	ksEntityPtr pMirCopy = pPart->NewEntity(o3d_mirrorOperation);
	ksMirrorCopyDefinitionPtr MirCopDef = pMirCopy->GetDefinition();
	MirCopDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
	ksEntityCollectionPtr MirColl = MirCopDef->GetOperationArray();			//������ ������ � �������� �������� ������ ��� ��������������
	MirColl->Clear();
	MirColl->Add(pExtrudeZenk);
	MirColl->Add(pExtrudeHoleSmall);
	pMirCopy->Create();

	pDoc->SaveAs("D:\\Projects\\C++\\2 �������\\����������� ���\\Detail.m3d");

}

