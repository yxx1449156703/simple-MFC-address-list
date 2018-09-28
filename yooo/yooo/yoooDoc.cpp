
// yoooDoc.cpp : CyoooDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "yooo.h"
#endif

#include "yoooDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CyoooDoc

IMPLEMENT_DYNCREATE(CyoooDoc, CDocument)

BEGIN_MESSAGE_MAP(CyoooDoc, CDocument)
END_MESSAGE_MAP()


// CyoooDoc ����/����

CyoooDoc::CyoooDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CyoooDoc::~CyoooDoc()
{
}

BOOL CyoooDoc::OnNewDocument()
{
	isnew=true;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CyoooDoc ���л�

void CyoooDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
		numbers.Serialize(ar);
		names.Serialize(ar);
		phones.Serialize(ar);
		emails.Serialize(ar);
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		numbers.Serialize(ar);
		names.Serialize(ar);
		phones.Serialize(ar);
		emails.Serialize(ar);
	}
	isnew=false;
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CyoooDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CyoooDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CyoooDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CyoooDoc ���

#ifdef _DEBUG
void CyoooDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CyoooDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CyoooDoc ����
