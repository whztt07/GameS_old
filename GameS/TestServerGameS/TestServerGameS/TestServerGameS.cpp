// TestServerGameS.cpp: ������� ���� �������.

#include "stdafx.h"
#include "Form1.h"

using namespace TestServerGameS;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// ��������� ���������� �������� Windows XP �� �������� �����-���� ��������� ����������
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	Form1^ form = gcnew Form1();
	// �������� �������� ���� � ��� ������
	Application::Run(form);
	return 0;
}
