#pragma once



// CMyPropertySheet

class CMyPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyPropertySheet)

public:
	CMyPropertySheet( UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMyPropertySheet( LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMyPropertySheet( );
	virtual ~CMyPropertySheet();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
};


