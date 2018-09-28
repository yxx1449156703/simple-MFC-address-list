
// yoooView.cpp : CyoooView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CyoooView ����/����

CyoooView::CyoooView()
	: CFormView(CyoooView::IDD)
{
	// TODO: �ڴ˴���ӹ������

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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CyoooView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();
	List.ModifyStyle(0, LVS_REPORT | LVS_SHOWSELALWAYS );
	List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_HEADERDRAGDROP | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	List.InsertColumn(0, _T("ѧ��"), 2, 100);
	List.InsertColumn(1, _T("����"), 2, 100);
	List.InsertColumn(2, _T("��ϵ��ʽ"), 2, 150);
	List.InsertColumn(3, _T("����"), 2, 200);
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


// CyoooView ���

#ifdef _DEBUG
void CyoooView::AssertValid() const
{
	CFormView::AssertValid();
}

void CyoooView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CyoooDoc* CyoooView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CyoooDoc)));
	return (CyoooDoc*)m_pDocument;
}
#endif //_DEBUG


// CyoooView ��Ϣ�������


void CyoooView::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CyoooDoc *doc=GetDocument();
	OnBnClickedButton3();
	int i = List.GetSelectionMark();
	if(i==-1)
		return ;
	CString a;
	a.Format(_T("ȷ��Ҫɾ����%s��������¼��"), doc->numbers[i]);
	if(IDOK!=MessageBox(a,"ɾ��ȷ����ʾ",MB_OKCANCEL))
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
