// Dialog1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "yooo.h"
#include "Dialog1.h"
#include "afxdialogex.h"


// CDialog1 �Ի���

IMPLEMENT_DYNAMIC(CDialog1, CDialogEx)

CDialog1::CDialog1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog1::IDD, pParent)
	, number(_T(""))
	, name(_T(""))
	, phone(_T(""))
	, email(_T(""))
{

}

CDialog1::~CDialog1()
{
}

void CDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, number);
	DDX_Text(pDX, IDC_EDIT2, name);
	DDX_Text(pDX, IDC_EDIT3, phone);
	DDX_Text(pDX, IDC_EDIT4, email);
}


BEGIN_MESSAGE_MAP(CDialog1, CDialogEx)
END_MESSAGE_MAP()


// CDialog1 ��Ϣ�������
