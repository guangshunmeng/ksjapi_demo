// MyPropertySheet.cpp : 实现文件
//

#include "stdafx.h"
//#include "KSJShow.h"
#include "MyPropertySheet.h"


// CMyPropertySheet

IMPLEMENT_DYNAMIC(CMyPropertySheet, CPropertySheet)

CMyPropertySheet::CMyPropertySheet() : CPropertySheet()
{

}

CMyPropertySheet::CMyPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CMyPropertySheet::CMyPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CMyPropertySheet::~CMyPropertySheet()
{
	OutputDebugString( _T("CMyPropertySheet::~CMyPropertySheet") );
}


BEGIN_MESSAGE_MAP(CMyPropertySheet, CPropertySheet)

END_MESSAGE_MAP()


// CMyPropertySheet 消息处理程序
void CMyPropertySheet::PostNcDestroy()
{
	int nPages = GetPageCount();
	for (int i = (nPages - 1); i >= 0; i--)
	{
		CPropertyPage* pPage = GetPage( i );
		ASSERT(pPage);
		if ( pPage )
		{
			delete pPage;
			RemovePage( i );
			TRACE("[CMyPropertySheet::OnDestroy] Removing page %ldn", i);
		}
	}

	CPropertySheet::PostNcDestroy();
}

