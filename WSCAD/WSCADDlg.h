
// WSCADDlg.h : ���� ���������
//

#pragma once


// ���������� ���� CWSCADDlg
class CWSCADDlg : public CDialog
{
// ��������
public:
	CWSCADDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WSCAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	double m_Width;
	double m_Depth;
	double m_Height;
	double m_lFaskaAll;

	double m_hDna;
	double m_dHoleSmall;
	double m_dZenk;
	double m_lInterHole;
	double m_rRound;

	double m_WidthTower;
	double m_lCek;
	double m_dCek;
	double m_dHoleBig;
	double m_hToHole;
	double m_lFaskaTower;
	double m_dHoleUpper;

	afx_msg void OnBnClickedButtonBuild();
	bool CheckData();
	afx_msg void OnBnClickedOk();
};
