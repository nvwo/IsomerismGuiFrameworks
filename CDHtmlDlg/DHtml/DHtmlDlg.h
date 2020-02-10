
// DHtmlDlg.h : 头文件
//

#pragma once


// CDHtmlDlg 对话框
class CDHtmlDlg : public CDHtmlDialog
{
// 构造
public:
	CDHtmlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DHTML_DIALOG, IDH = IDR_HTML_DHTML_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()

	//===
	DECLARE_DISPATCH_MAP()

	//  !!! 覆盖基类的这个方法

	BOOL CanAccessExternal()
	{
		// we trust all com object (haha, you can make virus)
		return TRUE;
	}


	void Test();
	// 自定义方法

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
