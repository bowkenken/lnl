#include "stdafx.h"

#using <mscorlib.dll>

using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;

//
// ������֥�˴ؤ�����̾���ϰʲ��� 
// °�����åȤ��̤������椵��ޤ���������֥�˴�Ϣ�դ����Ƥ��������ѹ�����ˤϡ�
// ������°���ͤ��ѹ����Ƥ���������
//
[assembly:AssemblyTitleAttribute("")];
[assembly:AssemblyDescriptionAttribute("")];
[assembly:AssemblyConfigurationAttribute("")];
[assembly:AssemblyCompanyAttribute("")];
[assembly:AssemblyProductAttribute("")];
[assembly:AssemblyCopyrightAttribute("")];
[assembly:AssemblyTrademarkAttribute("")];
[assembly:AssemblyCultureAttribute("")];		

//
// ������֥�ΥС���������ϡ��ʲ��� 4 �Ĥ�°���ǹ�������ޤ� :
//
//      Major Version
//      Minor Version 
//      Build Number
//      Revision
//
// ���ˤ���褦�ˡ�'*' ��Ȥäơ����٤Ƥ��ͤ���ꤹ�뤫��
// �ӥ�ɤ���ӥ�ӥ�����ֹ������ͤˤ��뤳�Ȥ��Ǥ��ޤ���

[assembly:AssemblyVersionAttribute("1.0.*")];

//
// ������֥�˽�̾����ˤϡ����Ѥ��륭������ꤷ�ʤ���Фʤ�ޤ��󡣥�����֥��̾�˴ؤ��� 
// �ܺ٤ˤĤ��Ƥϡ�Microsoft .NET Framework �ɥ�����Ȥ򻲾Ȥ��Ƥ���������
//
// ����°����Ȥäơ���̾�˻Ȥ����������椷�ޤ���
//
// ��� : 
//   (*) ���������ꤵ��ʤ��ȡ�������֥�Ͻ�̾����ޤ���
//   (*) KeyName �ϡ�����ԥ塼���˥��󥹥ȡ��뤵��Ƥ���Ź極���ӥ� �ץ�Х��� (CSP) ��
//       ɽ���ޤ���KeyFile �ϡ�������ޤ�
//       �ե�����Ǥ���
//   (*) KeyFile ����� KeyName ���ͤ����˻��ꤵ��Ƥ����硢 
//       �ʲ��ν�����ȯ�����ޤ� :
//       (1) KeyName �� CSP �˸��Ĥ��ä���硢���Υ������Ȥ��ޤ���
//       (2) KeyName ��¸�ߤ�����KeyFile ��¸�ߤ����硢
//           KeyFile �ˤ��륭���� CSP �˥��󥹥ȡ��뤵�졢�Ȥ��ޤ���
//   (*) KeyFile ���������ˤϡ�sn.exe (Strong Name) �桼�ƥ���ƥ���ȤäƤ���������
//        KeyFile ����ꤹ��Ȥ���KeyFile �ξ��ϡ�
//        �ץ������Ƚ��� �ǥ��쥯�ȥ�ؤ����Хѥ��Ǥʤ���Фʤ�ޤ���
//   (*) �ٱ��̾�Ϲ��٤ʥ��ץ����Ǥ����ܺ٤ˤĤ��Ƥ� Microsoft .NET Framework
//       �ɥ�����Ȥ򻲾Ȥ��Ƥ���������
//
[assembly:AssemblyDelaySignAttribute(false)];
[assembly:AssemblyKeyFileAttribute("")];
[assembly:AssemblyKeyNameAttribute("")];

