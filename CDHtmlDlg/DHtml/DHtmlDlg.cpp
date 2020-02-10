
// DHtmlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DHtml.h"
#include "DHtmlDlg.h"
#include "afxdialogex.h"
#include "atlsafe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDHtmlDlg �Ի���

BEGIN_DHTML_EVENT_MAP(CDHtmlDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()

BEGIN_DISPATCH_MAP(CDHtmlDlg, CDHtmlDialog)
	DISP_FUNCTION(CDHtmlDlg, "set_pos", set_pos, VT_BOOL, VTS_I4 VTS_I4) 
	DISP_FUNCTION(CDHtmlDlg, "GetSrInfo", GetSrInfo, VT_VARIANT, VTS_NONE)
	DISP_FUNCTION(CDHtmlDlg, "GetString", GetString, VT_VARIANT, VTS_NONE)
END_DISPATCH_MAP()
//VT_EMPTY, VTS_NONE

CDHtmlDlg::CDHtmlDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(IDD_DHTML_DIALOG, IDR_HTML_DHTML_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDHtmlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDHtmlDlg, CDHtmlDialog)
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CDHtmlDlg ��Ϣ�������

BOOL CDHtmlDlg::OnInitDialog()
{
	CDHtmlDialog::OnInitDialog();

	EnableAutomation();
	LPDISPATCH pDisp = GetIDispatch(FALSE);
	SetExternalDispatch(pDisp);

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//Navigate(L"file://E:/dev/MFC/DHtml/DHtml/1.html");//www.baidu.com

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDHtmlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDHtmlDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDHtmlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDHtmlDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDHtmlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CDHtmlDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	IHTMLDocument2* pDoc = NULL;
	CDHtmlDialog::GetDHtmlDocument(&pDoc);

	DISPPARAMS param = { 0 };
	VARIANT vtRet;
	CallJSFunction(pDoc, _T("CppCallJsFunc"), param, &vtRet, NULL, NULL);
	//OnOK();
	return S_OK;
}

HRESULT CDHtmlDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	Test();
	//OnCancel();
	return S_OK;
}

BOOL CDHtmlDlg::set_pos(int x, int y)
{
	AfxMessageBox(TEXT("Test"));
	printf("tr");
	return true;
}

//CComSafeArray<VARIANT>  m_oArrSrInfo(3,3);
VARIANT CDHtmlDlg::GetSrInfo()
{
	HRESULT hr = E_FAIL;
	VARIANT stVar;

	::VariantInit(&stVar);
	//V_VT(&stVar) = VT_EMPTY;
	//BSTR bstr;
	//bstr = SysAllocString(L"hello");

	CComSafeArray<VARIANT>  m_oArrSrInfo(3);
	//m_oArrSrInfo.Add(CComVariant(bstr));
	//srand(time(0));
	int rd = rand() / 10000 * 1000 + 1;
	m_oArrSrInfo.GetAt(0)= CComVariant(rd);
	m_oArrSrInfo.GetAt(1) = CComVariant(2);
	m_oArrSrInfo.GetAt(2) = CComVariant(3);
	//SysFreeString(bstr);

	V_VT(&stVar) = VT_ARRAY | VT_VARIANT;
	V_ARRAY(&stVar) = m_oArrSrInfo.Detach();;

	return stVar;
}

VARIANT CDHtmlDlg::GetString()
{
	VARIANT varStr;
	BSTR bstr;
	bstr = SysAllocString(L"hello");
	::VariantInit(&varStr);
	V_VT(&varStr) = VT_BSTR;
	V_BSTR(&varStr) = bstr;

	SysFreeString(bstr);
	return varStr;
}

HRESULT CDHtmlDlg::CallJSFunction(IHTMLDocument2* pDoc2,
	CString strFunctionName,
	DISPPARAMS dispParams,
	VARIANT* varResult,
	EXCEPINFO* exceptInfo,
	UINT* nArgErr)
{
	IDispatch *pDispScript = NULL;
	HRESULT hResult;
	hResult = pDoc2->get_Script(&pDispScript);
	if (FAILED(hResult))
	{
		return S_FALSE;
	}

	DISPID   dispid;
	CComBSTR objbstrValue = strFunctionName;
	BSTR bstrValue = objbstrValue.Copy();
	OLECHAR *pszFunct = bstrValue;
	hResult = pDispScript->GetIDsOfNames(IID_NULL,
		&pszFunct,
		1,
		LOCALE_SYSTEM_DEFAULT,
		&dispid);
	if (FAILED(hResult))
	{
		pDispScript->Release();
		return hResult;
	}

	varResult->vt = VT_VARIANT;
	hResult = pDispScript->Invoke(dispid,
		IID_NULL, LOCALE_USER_DEFAULT,
		DISPATCH_METHOD,
		&dispParams,
		varResult,
		exceptInfo,
		nArgErr);
	pDispScript->Release();

	return hResult;
}

void CDHtmlDlg::Test()
{
	AfxMessageBox(TEXT("Test"));

	CComPtr<IHTMLDocument2> pDoc2;
	HRESULT hr = GetDHtmlDocument(&pDoc2);
	if (SUCCEEDED(hr))
	{
		// change whatever element you want here with pDoc2...

		// ... and save the doc
		CComQIPtr<IHTMLDocument3> pDoc3 = pDoc2;
		CComBSTR docStr;
		CComPtr<IHTMLElement> pElem;
		hr = pDoc3->get_documentElement(&pElem);
		if (SUCCEEDED(hr))
		{
			hr = pElem->get_innerHTML(&docStr);
			FILE* f = NULL;
			fopen_s(&f,"1.html", "w");
			if (f)
			{
				CStringA str(docStr);
				fwrite(str.GetBuffer(), 1, str.GetLength(), f);
				fclose(f);
			}
		}
		//IHTMLElement* pbody = NULL;
		//m_spHtmlDoc->get_body(&pbody);
		//pbody->put_innerHTML(_bstr_t("<p>It <b>works</b>!</p>"));
	}
}

/*
void CHtmlDialogDlg::OnDocumentComplete(LPDISPATCH pDisp, LPCTSTR szUrl)
{
CDHtmlDialog::OnDocumentComplete(pDisp, szUrl);
IHTMLElement* pbody = NULL;
m_spHtmlDoc->get_body(&pbody);
pbody->put_innerHTML(_bstr_t("<p>It <b>works</b>!</p>"));

}

CString str("<html><body>frrrr</body></html>");
BSTR b(str.AllocSysString());
SetElementText("<html>", b);
void CDHtmlDialog::SetElementText(LPCTSTR szElementId, BSTR bstrText)
{
CComPtr<IHTMLElement> sphtmlElem;
GetElement(szElementId, &sphtmlElem);
if (sphtmlElem)
sphtmlElem->put_innerText(bstrText);
}
*/