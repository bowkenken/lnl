// stdafx.h : ɸ��Υ����ƥ� ���󥯥롼�� �ե�����Υ��󥯥롼�� �ե����롢�ޤ���
// ���Ȳ����¿�������Ĥ��ޤ��ѹ�����ʤ����ץ����������ѤΥ��󥯥롼�� �ե�����
// �򵭽Ҥ��ޤ���

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Windows �إå���������Ѥ���Ƥ��ʤ���ʬ��������ޤ���
#endif

// ���ǻ��ꤵ�줿����������оݥץ�åȥե��������ꤷ�ʤ���Фʤ�ʤ���硢�ʲ���������ѹ����Ƥ���������
// �ۤʤ�ץ�åȥե�������б������ͤ˴ؤ���ǿ�����ˤĤ��Ƥϡ�MSDN �򻲾Ȥ��Ƥ���������
#ifndef WINVER				// Windows 95 ����� Windows NT 4 �ʹߤΥС������˸�ͭ�ε�ǽ�λ��Ѥ���Ĥ��ޤ���
#define WINVER 0x0400		// ����� Windows 98 ����� Windows 2000 �ޤ��Ϥ���ʹߤΥС�����������Ŭ�ڤ��ͤ��ѹ����Ƥ���������
#endif

#ifndef _WIN32_WINNT		// Windows NT 4 �ʹߤΥС������˸�ͭ�ε�ǽ�λ��Ѥ���Ĥ��ޤ���
#define _WIN32_WINNT 0x0400		// ����� Windows 98 ����� Windows 2000 �ޤ��Ϥ���ʹߤΥС�����������Ŭ�ڤ��ͤ��ѹ����Ƥ���������
#endif						

#ifndef _WIN32_WINDOWS		// Windows 98 �ʹߤΥС������˸�ͭ�ε�ǽ�λ��Ѥ���Ĥ��ޤ���
#define _WIN32_WINDOWS 0x0410 // ����� Windows Me �ޤ��Ϥ���ʹߤΥС�����������Ŭ�ڤ��ͤ��ѹ����Ƥ���������
#endif

#ifndef _WIN32_IE			// IE 4.0 �ʹߤΥС������˸�ͭ�ε�ǽ�λ��Ѥ���Ĥ��ޤ���
#define _WIN32_IE 0x0400	// ����� IE 5.0  �ޤ��Ϥ���ʹߤΥС�����������Ŭ�ڤ��ͤ��ѹ����Ƥ���������
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ������ CString ���󥹥ȥ饯��������Ū�Ǥ���

// ����Ū��̵�뤷�Ƥ������ MFC �ηٹ��å������ΰ�������ɽ���������ޤ���
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �Υ��������ɸ�ॳ��ݡ��ͥ��
#include <afxext.h>         // MFC �γ�ĥ��ʬ

#include <afxdtctl.h>		// MFC �� Internet Explorer 4 ����� ����ȥ��� ���ݡ���
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC �� Windows ����� ����ȥ��� ���ݡ���
#endif // _AFX_NO_AFXCMN_SUPPORT

// bowkenken BEGIN
#include <MMSystem.h>
#include <afxdlgs.h>
#pragma comment( lib, "winmm.lib" )
// bowkenken END
