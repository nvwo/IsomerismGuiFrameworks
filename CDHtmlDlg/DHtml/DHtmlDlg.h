
// DHtmlDlg.h : ͷ�ļ�
//

#pragma once


// CDHtmlDlg �Ի���
class CDHtmlDlg : public CDHtmlDialog
{
// ����
public:
	CDHtmlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DHTML_DIALOG, IDH = IDR_HTML_DHTML_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()

	//===
	DECLARE_DISPATCH_MAP()

	//  !!! ���ǻ�����������

	BOOL CanAccessExternal()
	{
		// we trust all com object (haha, you can make virus)
		return TRUE;
	}


	void Test();
	// �Զ��巽��

	BOOL set_pos(int x, int y);
	VARIANT GetSrInfo();
	VARIANT GetString();

	HRESULT CallJSFunction(IHTMLDocument2* pDoc2,
		CString strFunctionName,
		DISPPARAMS dispParams,
		VARIANT* varResult,
		EXCEPINFO* exceptInfo,
		UINT* nArgErr);
};
