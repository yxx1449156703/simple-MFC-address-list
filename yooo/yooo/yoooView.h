
// yoooView.h : CyoooView ��Ľӿ�
//

#pragma once

#include "resource.h"
#include "afxcmn.h"


class CyoooView : public CFormView
{
protected: // �������л�����
	CyoooView();
	DECLARE_DYNCREATE(CyoooView)

public:
	enum{ IDD = IDD_YOOO_FORM };

// ����
public:
	CyoooDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CyoooView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CListCtrl List;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // yoooView.cpp �еĵ��԰汾
inline CyoooDoc* CyoooView::GetDocument() const
   { return reinterpret_cast<CyoooDoc*>(m_pDocument); }
#endif

