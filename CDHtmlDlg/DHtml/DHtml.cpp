
// DHtml.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "DHtml.h"
#include "DHtmlDlg.h"
#include "Registry.hpp"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;
using namespace winreg;

// CDHtmlApp

BEGIN_MESSAGE_MAP(CDHtmlApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CDHtmlApp ����

CDHtmlApp::CDHtmlApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CDHtmlApp ����

CDHtmlApp theApp;

// CDHtmlApp ��ʼ��

BOOL CDHtmlApp::InitInstance()
{
	const wstring testSubKey = L"SOFTWARE\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_BROWSER_EMULATION";
	winreg::RegKey key(HKEY_CURRENT_USER, testSubKey);
	vector<wstring> subKeyNames = key.EnumSubKeys();
	wcout << L"Subkeys:\n";
	for (const auto& s : subKeyNames)
	{
		wcout << L"  [" << s << L"]\n";
	}
	wcout << L'\n';
	vector<pair<wstring, DWORD>> values = key.EnumValues();
	wcout << L"Values:\n";
	for (const auto& v : values)
	{
		wcout << L"  [" << v.first << L"](" << RegKey::RegTypeToString(v.second) << L")\n";
	}
	wcout << L'\n';

	key.Close();

	key.Open(HKEY_CURRENT_USER, testSubKey);
	const DWORD testDw = 0x2AF9;
	key.SetDwordValue(L"DHtml.exe", testDw);
	DWORD testDw1 = key.GetDwordValue(L"DHtml.exe");
	if (testDw1 != testDw)
	{
		wcout << L"RegKey::GetDwordValue failed.\n";
	}
	DWORD typeId = key.QueryValueType(L"DHtml.exe");
	if (typeId != REG_DWORD)
	{
		wcout << L"RegKey::QueryValueType failed for REG_DWORD.\n";
	}
	wcout << L"All right!! :)\n\n";

	const wstring testSubKey1 = L"SOFTWARE\\wow6432node\\Microsoft\\Internet Explorer\\Main\\FeatureControl\\FEATURE_BROWSER_EMULATION";
	winreg::RegKey key1(HKEY_CURRENT_USER, testSubKey1);
	vector<wstring> subKeyNames1 = key1.EnumSubKeys();
	wcout << L"Subkeys:\n";
	for (const auto& s : subKeyNames1)
	{
		wcout << L"  [" << s << L"]\n";
	}
	wcout << L'\n';
	vector<pair<wstring, DWORD>> values1 = key1.EnumValues();
	wcout << L"Values:\n";
	for (const auto& v : values1)
	{
		wcout << L"  [" << v.first << L"](" << RegKey::RegTypeToString(v.second) << L")\n";
	}
	wcout << L'\n';

	key1.Close();

	key1.Open(HKEY_CURRENT_USER, testSubKey1);
	const DWORD testDw2 = 0x2AF9;
	key1.SetDwordValue(L"DHtml.exe", testDw2);
	DWORD testDw3 = key1.GetDwordValue(L"DHtml.exe");
	if (testDw2 != testDw3)
	{
		wcout << L"RegKey::GetDwordValue failed.\n";
	}
	DWORD typeId2 = key1.QueryValueType(L"DHtml.exe");
	if (typeId2 != REG_DWORD)
	{
		wcout << L"RegKey::QueryValueType failed for REG_DWORD.\n";
	}
	wcout << L"All right!! :)\n\n";


	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CDHtmlDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

