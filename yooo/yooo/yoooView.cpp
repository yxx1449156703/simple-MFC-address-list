
// yoooView.cpp : CyoooView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "yooo.h"
#endif

#include "yoooDoc.h"
#include "yoooView.h"
#include "Dialog1.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CyoooView

IMPLEMENT_DYNCREATE(CyoooView, CFormView)

BEGIN_MESSAGE_MAP(CyoooView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON1, &CyoooView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CyoooView::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CyoooView::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CyoooView::OnBnClickedButton3)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CyoooView::OnLvnItemchangedList1)
END_MESSAGE_MAP()

// CyoooView 构造/析构

CyoooView::CyoooView()
	: CFormView(CyoooView::IDD)
{
	// TODO: 在此处添加构造代码

}

CyoooView::~CyoooView()
{
}

void CyoooView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, List);
}

BOOL CyoooView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CyoooView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();
	List.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS );
	List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	List.InsertColumn(0, _T("学号"), 2, 100);
	List.InsertColumn(1, _T("姓名"), 2, 100);
	List.InsertColumn(2, _T("联系方式"), 2, 150);
	List.InsertColumn(3, _T("邮箱"), 2, 200);
	if(GetDocument()->isnew)
		return ;
	CyoooDoc *doc=GetDocument();
	for(int i=0,fuck=doc->numbers.GetSize();i<fuck;i++){
	List.InsertItem(i,doc->numbers[i]);
	List.SetItemText(i,1,doc->names[i]);
	List.SetItemText(i,2,doc->phones[i]);
	List.SetItemText(i,3,doc->emails[i]);
	}
}

void CyoooView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CyoooView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CyoooView 诊断

#ifdef _DEBUG
void CyoooView::AssertValid() const
{
	CFormView::AssertValid();
}

void CyoooView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CyoooDoc* CyoooView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CyoooDoc)));
	return (CyoooDoc*)m_pDocument;
}
#endif //_DEBUG


// CyoooView 消息处理程序


void CyoooView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog1 dialog;
	CyoooDoc *doc=GetDocument();
	if(dialog.DoModal()!=IDOK)
		return ;
	for(int i=0;i<List.GetItemCount();i++){
		if(dialog.number.GetLength()!=0 && 0!=dialog.number.Compare(doc->numbers[i]))continue;
		if(dialog.name.GetLength()!=0 && 0!=dialog.name.Compare(doc->names[i]))continue;
		if(dialog.phone.GetLength()!=0 && 0!=dialog.phone.Compare(doc->phones[i]))continue;
		if(dialog.email.GetLength()!=0 && 0!=dialog.email.Compare(doc->emails[i]))continue;
		List.SetFocus();
		List.SetItemState(i,LVNI_FOCUSED | LVIS_SELECTED, LVNI_FOCUSED | LVIS_SELECTED);
	}
}


void CyoooView::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CyoooDoc *doc=GetDocument();
	OnBnClickedButton3();
	int i = List.GetSelectionMark();
	if(i==-1)
		return ;
	CString a;
	a.Format(_T("确认要删除“%s”这条记录吗？"), doc->numbers[i]);
	if(IDOK!=MessageBox(a,"删除确认提示",MB_OKCANCEL))
	return ;
	List.DeleteItem(i);
	doc->numbers.RemoveAt(i);
	doc->names.RemoveAt(i);
	doc->phones.RemoveAt(i);
	doc->emails.RemoveAt(i);
	doc->DoFileSave();
}


void CyoooView::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog1 dialog;
	if(dialog.DoModal()!=IDOK)
		return ;
	int i=List.GetItemCount();
	List.InsertItem(i, dialog.number);
	List.SetItemText(i, 1,dialog.name);
	List.SetItemText(i, 2,dialog.phone);
	List.SetItemText(i, 3,dialog.email);
	CyoooDoc *doc=GetDocument();
	doc->numbers.Add(dialog.number);
	doc->names.Add(dialog.name);
	doc->phones.Add(dialog.phone);
	doc->emails.Add(dialog.email);
	doc->DoFileSave();
}


void CyoooView::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = List.GetSelectionMark();
	if(i==-1)
		return ;
	CDialog1 dialog;
	CyoooDoc *doc=GetDocument();
	dialog.number = doc->numbers[i];
	dialog.name = doc->names[i];
	dialog.phone = doc->phones[i];
	dialog.email = doc->emails[i];
	if(dialog.DoModal()!=IDOK)
		return ;
	List.SetItemText(i, 0,dialog.number);
	List.SetItemText(i, 1,dialog.name);
	List.SetItemText(i, 2,dialog.phone);
	List.SetItemText(i, 3,dialog.email);
	doc->numbers[i]=dialog.number;
	doc->names[i]=dialog.name;
	doc->phones[i]=dialog.phone;
	doc->emails[i]=dialog.email;
	doc->DoFileSave();
}


void CyoooView::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
		*pResult = 0;
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
