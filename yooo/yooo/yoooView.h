
// yoooView.h : CyoooView 类的接口
//

#pragma once

#include "resource.h"
#include "afxcmn.h"


class CyoooView : public CFormView
{
protected: // 仅从序列化创建
	CyoooView();
	DECLARE_DYNCREATE(CyoooView)

public:
	enum{ IDD = IDD_YOOO_FORM };

// 特性
public:
	CyoooDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CyoooView();
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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CListCtrl List;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // yoooView.cpp 中的调试版本
inline CyoooDoc* CyoooView::GetDocument() const
   { return reinterpret_cast<CyoooDoc*>(m_pDocument); }
#endif

